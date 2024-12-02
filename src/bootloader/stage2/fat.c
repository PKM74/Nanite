#include "fat.h"
#include "stdio.h"
#include "memdefs.h"
#include "utility.h"

#define SECTOR_SIZE 512

#pragma pack(push,1)
typedef struct
{
	uint8_t BootJumpInstruction[3];
	uint8_t OemIdentifier[8];
	uint16_t BytesPerSector;
	uint8_t SectorsPerCluster;
	uint16_t ReservedSectors;
	uint8_t FatCount;
	uint16_t DirEntryCount;
	uint16_t TotalSectors;
	uint8_t MediaDescriptorType;
	uint16_t SectorsPerFat;
	uint16_t SectorsPerTrack;
	uint16_t Heads;
	uint32_t HiddenSectors;
	uint32_t LargeSectorCount;
	
//Extended Boot Record
	uint8_t DriveNumber;
	uint8_t _Reserved;
	uint8_t Signature;
	uint32_t VolumeId;			//Serial Can be whatever
	uint8_t VolumeLabel[11];		//11 Bytes MUST Be padded with spaces!
	uint8_t SystemId[8];		//8 Bytes padded with spaces (use MSWIN4.1 for best compatibility!)
	
} FAT_BootSector;
#pragma pack(pop)

typedef struct {
	union {
		FAT_BootSector Bootsector;
		uint8_t BootsectorBytes[SECTOR_SIZE];
	} BS;

} FAT_Data;

static FAT_Data far* g_Data;
static uint8_t far* g_Fat = NULL;
static FAT_DirectoryEntry far* g_RootDirectory = NULL;
static uint32_t g_RootDirectoryEnd;

bool FAT_ReadBootSector(FILE* disk) {
 	return DISK_ReadSectors(disk, 0, 1, &g_Data->BS.BootSectorBytes);
}

bool FAT_ReadFat(DISK* disk)
{
	return DISK_ReadSectors(disk, g_Data->g_BootSector.ReservedSectors, g_Data->g_BootSector.SectorsPerFat, g_Fat);
}

bool FAT_ReadRootDirectory(DISK* disk)
{
	uint32_t lba = g_Data->g_BootSector.ReservedSectors + g_Data->g_BootSector.SectorsPerFat * g_Data->g_BootSector.FatCount;
	uint32_t size = sizeof(FAT_DirectoryEntry) * g_Data->g_BootSector.DirEntryCount;
	uint32_t sectors = (size + g_Data->g_BootSector.BytesPerSector - 1) / g_Data->g_BootSector.BytesPerSector;
		
	g_RootDirectoryEnd = lba + sectors;
	return DISK_ReadSectors(disk, lba, sectors, g_RootDirectory);
}

bool FAT_Initialize(DISK* disk) {
	g_Data = (FAT_Data far*)MEMORY_FAT_ADDR;

	// read bootsector
	if (!FAT_ReadBootSector(disk)) {
		printf("FAT: Bootsector Read Failed!\r\n");
		return false;
	}

	// read FAT
	g_Fat = (uint8_t far*)(g_Data + sizeof(FAT_Data));
	uint32_t fatSize = g_Data->BS.Bootsector.BytesPerSector * g_Data->BS.BootSector.SectorsPerFat;
	if(sizeof(FAT_Data) + fatSize >= MEMORY_FAT_SIZE) {
		printf("FAT: Not Enough Memory to Read FAT!\r\nNeeded %u, Only Have %u\r\n", sizeof(FAT_Data) + fatSize, MEMORY_FAT_SIZE);
		return false;
	}

	if (!FAT_ReadFat(disk)) {
		printf("FAT: Failed to Read FAT!\r\n");
		return false;
	}
	// read root dir (/)
	g_RootDirectory = (FAT_DirectoryEntry far*)(g_Fat + fatSize);
	uint32_t rootDirSize = sizeof(FAT_DirectoryEntry) * g_Data->BS.BootSector.DirEntryCount;
	rootDirSize = align(rootDirSize, g_Data->BS.BootSector.BytesPerSector);

	if (sizeof(FAT_Data) + fatSize + rootDirSize >= MEMORY_FAT_SIZE) { 
		printf("FAT: Not Enough Memory to Read Root Directory!\r\nNeeded %u, Only Have %u\r\n", sizeof(FAT_Data) + fatSize + rootDirSize, MEMORY_FAT_SIZE);
		return false;	
	}

	if(!FAT_ReadRootDirectory(disk)) { 
		printf("FAT: Failed to Read Root Directory!\r\n");
		return false;
	}
}

FAT_File far* FAT_Open(DISK* disk, const char* path) { 
	
}

DirectoryEntry* findFile(const char* name)
{
	for (uint32_t i = 0; i < g_BootSector.DirEntryCount; i++)
	{
		if (memcmp(name, g_RootDirectory[i].Name, 11) == 0)
		return &g_RootDirectory[i];
		
	}

	return NULL;
}

bool readFile(DirectoryEntry* fileEntry, FILE* disk, uint8_t* outputBuffer)
{
	bool ok = true;
	uint16_t currentCluster = fileEntry->FirstClusterLow;

	do {
		uint32_t lba = g_RootDirectoryEnd + (currentCluster - 2) * g_BootSector.SectorsPerCluster;
		ok = ok && readSectors(disk, lba, g_BootSector.SectorsPerCluster, outputBuffer);
		outputBuffer += g_BootSector.SectorsPerCluster * g_BootSector.BytesPerSector;

		uint32_t fatIndex = currentCluster * 3 / 2;
		if (currentCluster % 2 == 0)
			currentCluster = (*(uint16_t*)(g_Fat + fatIndex)) & 0x0FFF;
		else
			currentCluster = (*(uint16_t*)(g_Fat + fatIndex)) >> 4;
			
	} while (ok && currentCluster < 0x0FF8);

	return ok;
}

int main(int argc, char** argv)
{
	if (argc < 3){
		printf("Syntax: %s <disk image> <file name>\n", argv[0]);
		return -1;
	}

	FILE* disk = fopen(argv[1], "rb");
	if (!disk) {
		fprintf(stderr, "Cannot open disk image %s!\n", argv[1]);
		return -1;
	}

	if (!readBootSector(disk)) {
		fprintf(stderr, "Could not read boot sector!\n");
		return -2;
	}

	if (!readFat(disk)) {
		fprintf(stderr, "Could not read FAT!\n");
		free(g_Fat);
		return -3;
	}

	if (!readRootDirectory(disk)) {
		fprintf(stderr, "Could not read root!\n");
		free(g_Fat);
		free(g_RootDirectory);
		return -4;
	}

	DirectoryEntry* fileEntry = findFile(argv[2]);
	if (!fileEntry) {
		fprintf(stderr, "Could not locate file %s!\n", argv[2]);
		free(g_Fat);
		free(g_RootDirectory);
		return -5;
	}

	uint8_t* buffer = (uint8_t*) malloc(fileEntry->Size + g_BootSector.BytesPerSector);
	if (!readFile(fileEntry, disk, buffer)) {
		fprintf(stderr, "Could not read file %s!\n", argv[2]);
		free(g_Fat);
		free(g_RootDirectory);
		free(buffer);
		return -5;
	}

	for (size_t i = 0; i < fileEntry->Size; i++)
	{
		if (isprint(buffer[i])) fputc(buffer[i], stdout);
		//else printf("<%02x>", buffer[i]);
	}
	printf("\n");
	
	free(g_Fat);
	free(g_RootDirectory);
	return 0;
}

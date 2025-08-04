/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include "util.h"

#include <stdio.h>

int string_length(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        ++i;
    }
    return i;
}

void append(char s[], char n) {
    int len = string_length(s);
    s[len] = n;
    s[len + 1] = '\0';
}

// void Print_Storage_Types(int masterFDDType, int slaveFDDType)
// {
//     // Master FDD
//     if (masterFDDType == 0) printf("No Master Floppy Drive Detected!\n");
//     if (masterFDDType == 1) printf("Master Floppy Drive Detected!\nType: 360 KB 5.25 Inch Drive\n");
//     if (masterFDDType == 2) printf("Master Floppy Drive Detected!\nType: 1.2 MB 5.25 Inch Drive\n");
//     if (masterFDDType == 3) printf("Master Floppy Drive Detected!\nType: 720 KB 3.5 Inch Drive\n");
//     if (masterFDDType == 4) printf("Master Floppy Drive Detected!\nType: 1.44 MB 3.5 Inch Drive\n");
//     if (masterFDDType == 5) printf("Master Floppy Drive Detected!\nType: 2.88 MB 3.5 Inch Drive\n");
//     // Slave FDD
//     if (slaveFDDType == 0) printf("No Slave Floppy Drive Detected!\n");
//     if (slaveFDDType == 1) printf("Slave Floppy Drive Detected!\nType: 360 KB 5.25 Inch Drive\n");
//     if (slaveFDDType == 2) printf("Slave Floppy Drive Detected!\nType: 1.2 MB 5.25 Inch Drive\n");
//     if (slaveFDDType == 3) printf("Slave Floppy Drive Detected!\nType: 720 KB 3.5 Inch Drive\n");
//     if (slaveFDDType == 4) printf("Slave Floppy Drive Detected!\nType: 1.44 MB 3.5 Inch Drive\n");
//     if (slaveFDDType == 5) printf("Slave Floppy Drive Detected!\nType: 2.88 MB 3.5 Inch Drive\n");
// }
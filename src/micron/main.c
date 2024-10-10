/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "tinydir.h"

//Varible Setup here
#define os "Nanite OS"
#define version "0.0.1a"
#define cursor ":\\>"
#define hostname "[NOT IMPLEMENTED YET]"
#define os_logo " _   _             _ _         _____ _____ \n| \\ | |           (_) |       |  _  /  ___|\n|  \\| | __ _ _ __  _| |_ ___  | | | \\ `--. \n| . ` |/ _` | '_ \\| | __/ _ \\ | | | |`--. \\\n| |\\  | (_| | | | | | ||  __/ \\ \\_/ /\\__/ /\n\\_| \\_/\\__,_|_| |_|_|\\__\\___|  \\___/\\____/                                            \n"
#define shell_logo "  __  __ _                      __    __  \n |  \\/  (_) ___ _ __ ___  _ __  \\ \\   \\ \\ \n | |\\/| | |/ __| '__/ _ \\| '_ \\(_) \\   \\ \\\n | |  | | | (__| | | (_) | | | |_ \\ \\  / /\n |_|  |_|_|\\___|_|  \\___/|_| |_(_) \\_\\/_/ \n                                          \n"
int invalid_command = 0;
int command_list_length = 10; //does not NEED to match command list's length just helps with slower machines to keep this small and it can get buggy if too large
int history_length = {0};
int max_files = 200;
char command_list[][15] = {"help","version","clear", "uname", "exit", "dir", "fetch", "time", "exec"};
char buffer[15][255];
char program_buffer[30][100];
char prog_buffer2;
char history[][255];
char time_buffer[80];
char exec_cmd_operand_list[15][15] = {"--help", "--nogui"};
char exec_cmd_dir_buffer[][255];


int main() {
	printf("Micron Shell Version " version " Starting...\n");
	
	stage2();
	return 0;
}

int stage2() {
	printf("Done Loading Shell!\n");
		printf("Currently Implemtented Commands:\n");
	for(int i = 0; i < command_list_length; i++) {
    	printf("%s ", &command_list[i]);}
	printf("\n");
	cursor_loop();
	return 0;
}

int cursor_loop() {
	printf(cursor); 
    scanf("%s", &buffer);
	//Command detection shiz
	if (strcmp(buffer[0],command_list[0]) == 0) {help_cmd();}
	else if (strcmp(buffer[0],command_list[1]) == 0) {version_cmd();}
	else if (strcmp(buffer[0],command_list[2]) == 0) {clear_cmd();}
	else if (strcmp(buffer[0],command_list[3]) == 0) {uname_cmd();}
	else if (strcmp(buffer[0],command_list[4]) == 0) {exit_cmd();}
	else if (strcmp(buffer[0],command_list[5]) == 0) {dir_cmd();}
	else if (strcmp(buffer[0],command_list[6]) == 0) {fetch_cmd();}
	else if (strcmp(buffer[0],command_list[7]) == 0) {time_cmd();}
	else if (strcmp(buffer[0],command_list[8]) == 0) {exec_cmd();}
	else {printf("Mircon: %s: Command not Found!\n", &buffer); clear_buffer();}
	cursor_loop();
	return 0;
 }

//Bulit in commands
int help_cmd() {
	printf("Built-in Commands:\n");
	for(int i = 0; i < command_list_length; i++) {
    	printf("%s ", &command_list[i]);}
	printf("\n");
	clear_buffer();
	cursor_loop();
	return 0;
 }
int version_cmd() {
	printf(shell_logo);
	printf("Version %s Made by Tyler McGurrin\nCopyright (C) 2024\n", &version);
	clear_buffer();
	cursor_loop();
	return 0;
 }
int clear_cmd() {
	for(int i = 0; i < 2500; i++) {
		printf("\n");
	}
	clear_buffer();
	cursor_loop();
	return 0;
 }
int uname_cmd() {
	printf("%s\n", &os);
	clear_buffer();
	cursor_loop();
	return 0;
}
int exit_cmd() {
	printf("Exiting Micron Shell...\n");
	exit(0);
}
int dir_cmd() {
tinydir_dir dir;
tinydir_open(&dir, "./");

while (dir.has_next)
{
	tinydir_file file;
	tinydir_readfile(&dir, &file);

	printf("%s", file.name);
	if (file.is_dir)
	{
		printf("/			DIR");
	}
	printf("\n");

	tinydir_next(&dir);
}

tinydir_close(&dir);
clear_buffer();
cursor_loop();
return 0;
}
int fetch_cmd() {
printf("Operating System:	 %s\nShell:			 Micron %s\nHostname:	 	%s\n",os,version,hostname);
	time_t t = time(NULL);
    printf("UTC Time:		%s", asctime(gmtime(&t)));
    printf("Local Time:		%s", asctime(localtime(&t)));
printf(os_logo);
clear_buffer();
cursor_loop();
return 0;	
}
int time_cmd() {
	time_t t = time(NULL);
    printf("UTC:       %s", asctime(gmtime(&t)));
    printf("Local:     %s", asctime(localtime(&t)));
clear_buffer();
cursor_loop();
return 0;
}
int exec_cmd() {
	if (strcmp(buffer[1], exec_cmd_operand_list[0]) == 0) {exec_cmd_help();}
	else {exec_cmd_gui(); clear_buffer();}
	cursor_loop();
	return 0;	
}


//Command Handlers

//Exec Handlers
int exec_cmd_gui() {
	printf("\nExec:>");
	scanf("%s", &program_buffer);
	if (strcmp(program_buffer[0],command_list[0]) == 0) {help_cmd();}
	else if (strcmp(program_buffer[0],command_list[1]) == 0) {version_cmd();}
	else if (strcmp(program_buffer[0],command_list[2]) == 0) {clear_cmd();}
	else if (strcmp(program_buffer[0],command_list[3]) == 0) {uname_cmd();}
	else if (strcmp(program_buffer[0],command_list[4]) == 0) {exit_cmd();}
	else if (strcmp(program_buffer[0],command_list[5]) == 0) {dir_cmd();}
	else if (strcmp(program_buffer[0],command_list[6]) == 0) {fetch_cmd();}
	else if (strcmp(program_buffer[0],command_list[7]) == 0) {time_cmd();}
	else {exec_cmd_dir();}
	//if (exec_cmd_dir_buffer){printf("Exec: %s: Executible not Found!\n", &buffer); clear_buffer();}

	clear_buffer();
	cursor_loop();
	return 0;
}

int exec_cmd_help() {
	printf("Usage [Operands Like:  ");
	for(int i = 0; i < command_list_length; i++) {
    	printf("%s ", &exec_cmd_operand_list[i]);}
	printf("]\n");
	clear_buffer();
	cursor_loop();
	return 0;
	}
int exec_cmd_dir() {
tinydir_dir dir;
tinydir_open(&dir, "./");

while (dir.has_next)
{
	tinydir_file file;
	tinydir_readfile(&dir, &file);

	for(int i = 0; i < max_files; i++) {
    buffer[i][255] = NULL;}	
	if (file.is_dir)
	{
		break;
	}
		for(int i = 0; i < max_files; i++) {
			if (strcmp(program_buffer,file.name) == 0) {
				printf("Loading program...");
				strcat(prog_buffer2, "./");
				strcat(prog_buffer2, program_buffer);
				prog_load();
			}
			else break;
		}
	
	}
	printf("Exec: %s: No Executible found!\n", &program_buffer);
	tinydir_next(&dir);
tinydir_close(&dir);
clear_buffer();
cursor_loop();
return 0;
}


//Extra Tools (Not executible via shell)
int clear_buffer() {

	for(int i = 0; i < command_list_length; i++) {
    	buffer[i][255] = NULL;}
	free(prog_buffer2);
	cursor_loop();
	return 0;
}
int prog_load() {
	system(prog_buffer2);
	exit(0);
}
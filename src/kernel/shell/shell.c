/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#include "shell.h"

#include <stdio.h>
#include "c_scan.h"

char* cursor = "=>";

/*
A simple Rescue shell
Because, Yes.
*/

void shell()
{
    printf("NANITE Rescue Shell");
    while(1 == 1) {
        printf("%s", cursor);
        c_scanf("");
    }

}

/*----------------*\
|Nanite OS         |
|Copyright (C) 2025|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#define incptr(p, n) ((void *)(((uintptr_t)(p)) + (n)))

int string_length(char s[]);
void append(char s[], char n);
void Print_Storage_Types(int masterFDDType, int slaveFDDType);
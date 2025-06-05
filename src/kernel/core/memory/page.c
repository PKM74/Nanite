/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include "page.h"

unsigned long* Page_Directory = (unsigned long*) 0x9c000;
unsigned long* Page_Table = (unsigned long*) 0x9d000

/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#pragma once

#include <stddef.h>

struct memory_block {
    size_t        size;
    char          free;
    struct memory_block  *next_free;
};

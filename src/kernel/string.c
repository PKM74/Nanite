/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include "string.h"
#include <stdint.h>
#include <stddef.h>

const char* strchr(const char* str, char chr) { 
    if (str == NULL)
        return NULL;

    while (*str) {
        if (*str == chr)
            return str;

        ++str;
    }

    return NULL;
}

char* strcpy(char* dst, const char* src) {
    char* origDst = dst;
    
    if (dst == NULL)
        return NULL;
    
    if (src == NULL) {
        *dst = '\0';
        return dst;
    }
    while (*src) { 
        *dst = *src;
        ++src;
        ++dst;
    }

    *dst = '\0'; 
    return origDst;
}

unsigned strlen(const char* str) {
    unsigned len = 0;
    while (*str) {
        ++len; ++str;
    }
    return len;
}

char* strcat(char *dest, const char *src) {
    char *original_dest = dest;
    while (*dest != '\0') {
        dest++;
    }
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return original_dest;
}
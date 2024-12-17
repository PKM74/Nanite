/*----------------*\
|Nanite OS         |
|Copyright (C) 2024|
|Tyler McGurrin    |
\*----------------*/
#include "ctype.h"

bool islower(char chr) {
    return chr >= 'a' && chr <= 'z';
}

char toupper(char chr) {
    return islower(chr) ? (chr - 'a' + 'A') : chr;
}

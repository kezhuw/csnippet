#ifndef __REMOVE_MULTIPLE_CHARACTERS_H
#define __REMOVE_MULTIPLE_CHARACTERS_H

#include <stddef.h>

// Combine continuous characters into one, return result string length.
// assert(str != NULL);
//
// e.g.:
//
// ("", '_')			==> ""
// ("mtttah", 't')		==> "mtah"
// ("_abxxx___c_d__e__", 'x')	==> "_abx___c_d__e__"
size_t remove_multiple_characters(char *str, int c);
#endif

#include "remove_multiple_characters.h"

#include <assert.h>

size_t
remove_multiple_characters(char *str, int c) {
	assert(str != 0);
	if (str[0] == '\0') {
		return 0;
	}
	char *next = str+1;
	char *iter = str+1;
	int prevc = *str;
	for (int iterc = *iter; (iterc = *iter) != '\0'; iter++) {
		if (iterc == c && prevc == iterc) {
			continue;
		}
		*next++ = iterc;
		prevc = iterc;
	}
	*next = '\0';
	return next-str;
}

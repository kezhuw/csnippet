#include "remove_multiple_characters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *
dupstr(const char *str) {
	size_t len = strlen(str);
	char *ret = malloc(len+1);
	strcpy(ret, str);
	return ret;
}

static void
delstr(char *dup) {
	free(dup);
}

struct pair {
	char *origin;
	char *expect;
};

static const struct pair space_pairs[] = {
	{"", ""},
	{" ", " "},
	{"    ", " "},
	{"   a", " a"},
	{"a   ", "a "},
	{"   a    ", " a "},
	{"   abcdef    ", " abcdef "},
	{"   abcdef    fe  ", " abcdef fe "},
	{"    abc    def  ghi  opq", " abc def ghi opq"},
	{"   \n    \nabc  cde  ", " \n \nabc cde "},
	{NULL, NULL},
};

static const struct pair a_pairs[] = {
	{"", ""},
	{"   a   ", "   a   "},
	{"aaa bbb ccc___   aaa   ", "a bbb ccc___   a   "},
	{"___a__aa__a_aaaa_", "___a__a__a_a_"},
	{NULL, NULL},
};

struct remove {
	long c;
	const struct pair *t;
};

static const struct remove remove_space = {' ', space_pairs};
static const struct remove remove_a = {'a', a_pairs};

static void
ForeachPairs(const struct pair *t, int c, void (*each)(const struct pair *p, int c)) {
	const struct pair *i;
	for (i = t; i->origin != NULL; i++) {
		each(i, c);
	}
}

// TODO Escape special characters, e.g., \n, \t.
static void
CheckReturn(const struct pair *p, int c) {
	char *str = dupstr(p->origin);
	size_t len = remove_multiple_characters(str, c);
	if (len != strlen(str)) {
		fprintf(stderr,
			"remove_multiple_characters(%s, %c) got {{%s}}, length %zu, return %zu.\n",
			p->origin, c, str, strlen(str), len);
		abort();
	}
	delstr(str);
}

static void
CheckExpect(const struct pair *p, int c) {
	char *str = dupstr(p->origin);
	remove_multiple_characters(str, c);
	if (strcmp(str, p->expect) != 0) {
		fprintf(stderr,
			"remove_multiple_characters(%s, %c) got {{%s}}, expect {{%s}}.\n",
			p->origin, c, str, p->expect);
		abort();
	}
	delstr(str);
}

static void
TestReturn(const struct remove *r) {
	ForeachPairs(r->t, r->c, CheckReturn);
}

static void
TestExpect(const struct remove *r) {
	ForeachPairs(r->t, r->c, CheckExpect);
}

int
main(void) {
	setvbuf(stderr, 0, _IONBF, 0);
	setvbuf(stdout, 0, _IONBF, 0);

	TestReturn(&remove_space);
	TestReturn(&remove_a);

	TestExpect(&remove_space);
	TestExpect(&remove_a);

	fprintf(stdout, "remove_multiple_characters PASSED\n");

	return 0;
}

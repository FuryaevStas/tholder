#ifndef	_PARSER_H_
#define _PARSER_H_

#include "core.h"

#define SIZE_OF(a) (sizeof((a))/sizeof(char*))

enum Directive {
	DIR_NONE,
	DIR_FILE,
	DIR_DIR
};

extern const char *syntax[];

size_t wrdlen(char *_wrd);
char *nextWord(char *_buffer);
size_t isDirective(char *_wrd);

#endif//_PARSER_H_
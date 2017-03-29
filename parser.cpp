#include "parser.h"

const char *syntax[] = {
	"",
	"file:",
	"dir:"
};

size_t wrdlen(char *_wrd)
{
    const char *_st(_wrd);
    for (; *_st != '\0' && *_st != ' '; _st++);
    return (_st - _wrd);
}

char *nextWord(char *_buffer)
{
	static char *pntr(_buffer), *prev(NULL);
	if (pntr == prev)
		pntr++;
	while (*pntr < 'a' || *pntr > 'z')
	{
		if (*pntr == EOF)
			return pntr;
		pntr++;
	}
	prev = pntr;
	return pntr;
}

size_t isDirective(char *_wrd)
{
	size_t _res(DIR_NONE);
	for (size_t i(1); i < SIZE_OF(syntax); i++)
		if(!strcmp(syntax[i], _wrd))
			_res = i;
	return _res;
}
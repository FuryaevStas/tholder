#include "core.h"

const char* program_name;
const char* data_path = "./templates/";

enum Modes {
	MODE_NONE,
	MODE_ADD,
	MODE_REM,
	MODE_LIST,
	MODE_LOAD
};

const char* modes[] = {
	"",
	"add",
	"remove",
	"list",
	"load"
};

void printUsage(FILE *_stream, int _excode)
{
	fprintf(_stream,    "Usage: %s options [add / remove / list / load]"
						"[*input files / template name]\n"
						"\tadd [name] [input path]\n"
						"\tload/remove [name]\n", program_name);
	exit(_excode);
}

int main(int argc, char *argv[])
{
	int mode(MODE_NONE);
	program_name = argv[0];

	if (argc < 2)
		printUsage(stderr, 1);

	for (size_t i(1); i < SIZE_OF(modes); i++)
		if (!strcmp(modes[i], argv[1]))
			mode = i;

	switch (mode){
		case MODE_NONE:
			printUsage(stderr, 1);

		case MODE_ADD:
			if (argc == 4)
				add(argv[2], argv[3]);
			else
				printUsage(stderr, 1);
			break;

		case MODE_REM:
			if (argc == 3)
				rem(argv[2]);
			else
				printUsage(stderr, 1);
			break;

		case MODE_LIST:
			listAll();
			break;
		
		case MODE_LOAD:
			if (argc == 4)
				load(argv[2]);
			else
				printUsage(stderr, 1);
			break;
	}

	return 0;
}
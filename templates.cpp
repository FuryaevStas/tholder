#include "templates.h"

DIR *tplt_dir;
struct stat path_stat;
struct dirent *tplt;

struct section
{
	const char *fname;

	section(const char* _fname)
	{
		this->fname = _fname;
	}
};

vector<section> sections;

bool isReg(const char *_path)
{
    struct stat path_stat;
    stat(_path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

char* getPath(const char *_prefix, const char *_name)
{
    static char path_buf[1024];
    memset(path_buf, 0, SIZE_OF(path_buf));
    strcat(path_buf, _prefix);
    strcat(path_buf, _name);
    return path_buf;
}

void listAll()
{
    tplt_dir = opendir(data_path);
    while ((tplt = readdir(tplt_dir)) != NULL)
	if (isReg(getPath(data_path, tplt->d_name)))
	    printf("%s\n", tplt->d_name);
    closedir(tplt_dir);
}

void add(const char *_name, const char *_path)
{
    if (access(getPath(data_path, _name), F_OK) != -1)
    {
        perror("Error creating template");
        exit(1);
    }
    stat(_path, &path_stat);
    
    if (S_ISREG(path_stat.st_mode))
        sections.push_back(section(_path));
	else
		;	// Make recurcive folder processing
	FILE *in = fopen(_path, "r");
	FILE *out = fopen(getPath(data_path, _name), "w");
	for (std::vector<section>::iterator it = sections.begin(); it != sections.end(); ++it)
	{
		fprintf(out, "%s %s\n", syntax[DIR_FILE], _path);
		fseek(in, 0, SEEK_END);
		size_t size = ftell(in);
		rewind(in);
		char *io_buffer = (char*) malloc (sizeof(char) * size);
		fread(io_buffer, 1, size, in);
		fwrite(io_buffer, 1, size, out);
		free(io_buffer);
	}
	fclose(out);
	fclose(in);
}

void rem(const char *_name)
{
    if (access(getPath(data_path, _name), F_OK) != -1)
    {
        if (remove(getPath(data_path, _name)))
            perror("Error deleting");
    }
    else
        perror("Error deleting");
}

void load(const char *_name)
{
	FILE *in;
	if ((in = fopen(getPath(data_path, _name), "r")) == NULL)
	{
		perror("Error");
		exit(1);
	}
	fseek(in, 0, SEEK_END);
	size_t size = ftell(in);
	rewind(in);
	char *io_buffer = (char*) malloc (sizeof(char) * size);
	fread(io_buffer, 1, size, in);
	fclose(in);
	char *pt(NULL);
	while (*(pt = nextWord(io_buffer)) != EOF && !isDirective(pt))
	{
		size = pt - io_buffer;
	}
}
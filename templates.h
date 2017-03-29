#ifndef _TEMPLATES_H_
#define _TEMPLATES_H_

#include <dirent.h>

#include "core.h"

struct section;

bool isReg(const char *_path);
char* getPath(const char *_prefix, const char *_name);
void listAll();
void add(const char *_name, const char *_path);
void rem(const char *_name);
void load(const char *_name);


#endif//_TEMPLATES_H_
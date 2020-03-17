#ifndef READSAVEFILE_H
#define READSAVEFILE_H

#include "generation.h"

int saveToFile(generation_t* gen, char* name);
generation_t* readFromFile(char* filepath);

#endif

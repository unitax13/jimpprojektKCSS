#ifndef READSAVEFILE_H
#define READSAVEFILE_H

#include "generation.h"

/* Funkcja zapisujaca generacji do pliku o podanej nazwie */
int saveToFile(generation_t* gen, char* name);

/* Funkcje odczytujaca generacje z pliku o podanej nazwie */
generation_t* readFromFile(char* filepath);

#endif

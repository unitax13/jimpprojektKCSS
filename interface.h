#ifndef INTERFACE_H
#define INTERFACE_H

#include "generation.h"

/* Funkcja, ktora odpowiada za interfejs
 * utworzenia/otworzenia generacji */
generation_t* initGenerationInput();

/* Funkcja, ktora odpowiada za interfejs
 * wszystkich opcji interakcji/zapisywania generacji */
int programIteration(generation_t* gen);

#endif

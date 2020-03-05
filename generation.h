#ifndef GENERATION_H
#define GENERATION_H

typedef enum { DEAD = 0, BORN, ALIVE } cell_t;

typedef struct {
	cell_t** cells;
	int width, height;
} generation_t;

generation_t* createNewGeneration(int width, int height);
int getCell(generation_t* gen, int x, int y); //zwraca -1 jesli podana komorka wykracza poza granice

#endif

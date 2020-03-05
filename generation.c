#include "generation.h"
#include <stdlib.h>

generation_t* createNewGeneration(int width, int height) {
	generation_t* newGen = malloc(sizeof(*newGen));
	newGen->cells = malloc(width * sizeof(cell_t*));
	for (int x = 0; x < width; x++) {
		newGen->cells[x] = malloc(height * sizeof(cell_t));
		for (int y = 0; y < height; y++)
			newGen->cells[x][y] = DEAD;
	}
	newGen->width = width;
	newGen->height = height;
}

int getCell(generation_t* gen, int x, int y) {
	if (x < 0 || x >= gen->width || y < 0 || y >= gen->height)
		return -1;
	return gen->cells[x][y];
}

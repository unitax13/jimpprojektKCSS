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
	newGen->generationNumber = 1;
}

int getCell(generation_t* gen, int x, int y) {
	if (x < 0 || x >= gen->width || y < 0 || y >= gen->height)
		return -1;
	return gen->cells[x][y];
}

static int cellIsAlive(generation_t* gen, int x, int y) {
	int cell = getCell(gen, x, y);
	return (cell == ALIVE || cell == DYING);
}

/* Funkcja pomocnicza zwracajaca ilosc zywych sasiadow */
static int getAliveNeighbours(generation_t* gen, int x, int y) {
	int neighbours = 0;
	if (cellIsAlive(gen, x - 1, y - 1)) neighbours++;
	if (cellIsAlive(gen, x, y - 1)) neighbours++;
	if (cellIsAlive(gen, x + 1, y - 1)) neighbours++;
	if (cellIsAlive(gen, x - 1, y)) neighbours++;
	if (cellIsAlive(gen, x + 1, y)) neighbours++;
	if (cellIsAlive(gen, x - 1, y + 1)) neighbours++;
	if (cellIsAlive(gen, x, y + 1)) neighbours++;
	if (cellIsAlive(gen, x + 1, y + 1)) neighbours++;
	return neighbours;
}

void nextGeneration(generation_t* gen) {
	for (int y = 0; y < gen->height; y++) {
		for (int x = 0; x < gen->width; x++) {
			int cell = getCell(gen, x, y);
			if (cell == DEAD) {
				if (getAliveNeighbours(gen, x, y) == 3)
					gen->cells[x][y] = BORN;
			} else if (cell == ALIVE) {
				int neighbours = getAliveNeighbours(gen, x, y);
				if (!(neighbours == 2 || neighbours == 3))
					gen->cells[x][y] = DYING;
			}
		}
	}
	for (int y = 0; y < gen->height; y++) {
		for (int x = 0; x < gen->width; x++) {
			int cell = getCell(gen, x, y);
			if (cell == BORN)
				gen->cells[x][y] = ALIVE;
			else if (cell == DYING)
				gen->cells[x][y] = DEAD;
		}
	}
	gen->generationNumber++;
}

int isGenerationDead(generation_t* gen) {
	for (int x = 0; x < gen->width; x++) {
		for (int y = 0; y < gen->height; y++) {
			if (gen->cells[x][y] == ALIVE)
				return 0;
		}
	}
	return 1;
}

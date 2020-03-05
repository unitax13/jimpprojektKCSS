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
    newGen->generationNumber=0;
}

int getCell(generation_t* gen, int x, int y) {
	if (x < 0 || x >= gen->width || y < 0 || y >= gen->height)
		return -1;
	return gen->cells[x][y];
}

/* Funkcja pomocnicza zwracajaca ilosc zywych sasiadow,
 * czyli liczaca komorki ALIVE przed komorka
 * i komorki BORN po komorce (bo jeszcze nie zostaly zamienione na ALIVE) */
static int getAliveNeighbours(generation_t* gen, int x, int y) {
	int neighbours = 0;
	if (getCell(gen, x - 1, y - 1) == 2) neighbours++;
	if (getCell(gen, x, y - 1) == 2) neighbours++;
	if (getCell(gen, x + 1, y - 1) == 2) neighbours++;
	if (getCell(gen, x - 1, y) == 2) neighbours++;
	if (getCell(gen, x + 1, y) >= 1) neighbours++;
	if (getCell(gen, x - 1, y + 1) >= 1) neighbours++;
	if (getCell(gen, x, y + 1) >= 1) neighbours++;
	if (getCell(gen, x + 1, y + 1) >= 1) neighbours++;
	return neighbours;
}

void nextGeneration(generation_t* gen) {
	for (int y = 0; y < gen->height; y++) {
		for (int x = 0; x < gen->width; x++) {
			int cell = getCell(gen, x, y);
			if (cell == DEAD) {
				if (getAliveNeighbours(gen, x, y) == 3)
					gen->cells[x][y] = BORN;
			} else if (cell == BORN || cell == ALIVE) {
				int neighbours = getAliveNeighbours(gen, x, y);
				if (!(neighbours == 2 || neighbours == 3)) {
					gen->cells[x][y] = DEAD;
					break;
				}
				gen->cells[x][y] = ALIVE; //ozywianie komorki (zamienianie BORN na ALIVE)
			}

		}
	}
    gen->generationNumber++;
}

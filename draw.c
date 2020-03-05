#include "draw.h"
#include <stdio.h>

void draw(generation_t* gen) {
	for (int y = 0; y < gen->height; y++) {
		for (int x = 0; x < gen->width; x++) {
			if (getCell(gen, x, y) == DEAD)
				printf("%c", '.');
			else
				printf("%c", '#');
		}
		printf("\n");
	}
}

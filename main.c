#include <stdlib.h>
#include <time.h>
#include "interface.h"
#include "draw.h"

int main() {
	srand(time(NULL));
	
	drawAuthors();
	generation_t* gen = initGenerationInput();
	if (gen == NULL)
		return 0;
	draw(gen);

	while (programIteration(gen) != 1);

	return 0;
}

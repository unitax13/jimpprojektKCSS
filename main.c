#include <stdio.h> //usun potem
#include "generation.h" //usun potem
#include "draw.h"

int main() {
	generation_t* gen = createNewGeneration(20, 10);
	draw(gen);

	return 0;
}

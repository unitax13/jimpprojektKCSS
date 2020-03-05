#include <stdio.h> //usun potem
#include <unistd.h>
#include "generation.h" //usun potem
#include "draw.h"

int main() {
	generation_t* gen = createNewGeneration(10, 10);
	draw(gen);
    sleep(1);
    gen->cells[3][9] = ALIVE;
    draw(gen);
	return 0;
}

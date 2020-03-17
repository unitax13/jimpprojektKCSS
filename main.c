#include <stdio.h> //usun potem
#include <stdlib.h> //zeby dzialalo system("clear")
#include <unistd.h>
#include <time.h>
#include "generation.h" //usun potem
#include "draw.h"
#include "saveimg.h"
#include "readsavefile.h"

#define SZEROKOSC 20
#define WYSOKOSC 10

int main() {
	srand(time(NULL));
	
	/*
	generation_t* gen = createNewGeneration(SZEROKOSC, WYSOKOSC);

	gen->cells[2][0] = ALIVE;
	gen->cells[2][1] = ALIVE;
	gen->cells[2][2] = ALIVE;
	gen->cells[1][2] = ALIVE;
	gen->cells[0][1] = ALIVE;

	gen->cells[9][5] = ALIVE;
	gen->cells[10][5] = ALIVE;
	gen->cells[9][6] = ALIVE;
	gen->cells[10][6] = ALIVE;
	
	saveToFile(gen, "losowy char");
	*/

	generation_t* gen = readFromFile("");

	while (1) {
		system("clear");
		draw(gen);
		sleep(1);
		//int rx = rand() % SZEROKOSC;
		//int ry = rand() % WYSOKOSC;
		//gen->cells[rx][ry] = ALIVE;
		nextGeneration(gen);
	}

	return 0;
}

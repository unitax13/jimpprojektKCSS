#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AUTHORS_WIDTH 29

void drawAuthors() {
	for (int i = 0; i < AUTHORS_WIDTH; i++)
		printf( (i % 4 == 0) ? "+" : "-" );
	printf("\n");
	char* s1 = "Autorzy:";
	printf("| %s", s1);
	for (int i = 0; i < AUTHORS_WIDTH - strlen(s1) - 3; i++)
		printf(" ");
	printf("|\n");
	char* s2 = "IMIE NAZWISKO, NR_INDEKSU";
	printf("| %s", s2);
	for (int i = 0; i < AUTHORS_WIDTH - strlen(s2) - 3; i++)
		printf(" ");
	printf("|\n");
	char* s3 = "Szymon Szafranski, 307405";
	printf("| %s", s3);
	for (int i = 0; i < AUTHORS_WIDTH - strlen(s3) - 3; i++)
		printf(" ");
	printf("|\n");
	for (int i = 0; i < AUTHORS_WIDTH; i++)
		printf( (i % 4 == 0) ? "+" : "-" );
	printf("\n");
}

void draw(generation_t* gen) {
	system("clear");
    printf("Generation #%d\n", gen->generationNumber);   
	printf("+");
	for (int x = 0; x < gen->width; x++)
		printf("-");
	printf("+\n");
	for (int y = 0; y < gen->height; y++) {
		printf("|");
		for (int x = 0; x < gen->width; x++) {
			if (getCell(gen, x, y) == DEAD)
				printf("%c", '.');
			else
				printf("%c", '#');
		}
		printf("|\n");
	}
	printf("+");
	for (int x = 0; x < gen->width; x++)
		printf("-");
	printf("+\n");
}

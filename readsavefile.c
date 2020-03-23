#include "readsavefile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int saveToFile(generation_t* gen, char* name)
{
	// modul dodajacy rozszerzenie .txt do nazwy pliku
	int namelen = 0;
	while (name[namelen]!='\0') namelen++;
	char finalname[namelen+4];
	for (int i=0; i<namelen; i++) finalname[i]=name[i];
	sprintf(finalname + namelen, ".txt");

	FILE *ouf = (strcmp(name, "") != 0) ? fopen(finalname, "w") : fopen("genstate.txt", "w");
    	if (ouf == NULL) return 1;
	fprintf(ouf, "%i %i %i\n", gen->generationNumber, gen->width, gen->height);
	for (int y = 0; y < gen->height; y++) {
		for (int x = 0; x < gen->width; x++) {
			if (getCell(gen, x, y) == DEAD)
				fprintf(ouf, "%c", '.');
			else
				fprintf(ouf, "%c", '#');
		}
		fprintf(ouf, "\n");
	}
    	fclose(ouf);
    	return 0;
}

generation_t* readFromFile(char* filepath) {
	FILE* f = (strcmp(filepath, "") != 0) ? fopen(filepath, "r") : fopen("genstate.txt", "r");
	if (f == NULL)
		return NULL;
	int number, width, height;
	if (fscanf(f, "%i %i %i", &number, &width, &height) != 3)
		return NULL;
	generation_t* gen = createNewGeneration(width, height);
	gen->generationNumber = number;
	char c;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (fscanf(f, "%c", &c) == 0)
				return NULL;
			if (c == '.')
				gen->cells[x][y] = DEAD;
			else if (c == '#')
				gen->cells[x][y] = ALIVE;
		}
		fscanf(f, "%c", &c); //pomijanie znaku nowej linii
	}
	fclose(f);
	return gen;
}

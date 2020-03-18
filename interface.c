#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include "draw.h"
#include "readsavefile.h"
#include "saveimg.h"

#define SLEEPTIME 200
#define GENERATION_WIDTH 20
#define GENERATION_HEIGHT 10

/* Funkcje pomocnicze do sleep() w milisekundach */
/* (z internetu) */
int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}




/* Funckje pomocnicze do wczytywania gotowych generacji */
static generation_t* loadGeneration1() {
	generation_t* gen = createNewGeneration(GENERATION_WIDTH, GENERATION_HEIGHT);
	gen->cells[2][0] = ALIVE;
	gen->cells[2][1] = ALIVE;
	gen->cells[2][2] = ALIVE;
	gen->cells[1][2] = ALIVE;
	gen->cells[0][1] = ALIVE;
	gen->cells[9][5] = ALIVE;
	gen->cells[9][6] = ALIVE;
	gen->cells[10][5] = ALIVE;
	gen->cells[10][6] = ALIVE;
	return gen;
}

static generation_t* loadGeneration2() {	
	generation_t* gen = createNewGeneration(GENERATION_WIDTH, GENERATION_HEIGHT);
	gen->cells[9][0] = ALIVE;
	gen->cells[11][0] = ALIVE;
	gen->cells[9][1] = ALIVE;
	gen->cells[10][1] = ALIVE;
	gen->cells[11][1] = ALIVE;
	gen->cells[10][2] = ALIVE;
	return gen;
}

/* Funkcje pomocnicze do wczytywania danych od uzytkownika */
static char* getStringInput(char* msg) {
	printf("%s", msg);
	char* s = malloc(sizeof(char) * 128);
	scanf("%s", s);
	return s;
}

generation_t* initGenerationInput() {
	printf("\n");
	printf("Wybierz opcje:\n");
	printf("1. Wczytaj generacje z pliku\n");
	printf("2. Wczytaj gotowa generacje nr 1\n");
	printf("3. Wczytaj gotowa generacje nr 2\n");
	printf("4. Zakoncz\n");
	char c;
	do {
		scanf(" %c", &c);
		if (c == '1') {
			char* s = getStringInput("Prosze podac nazwe pliku: ");
			generation_t* gen = readFromFile(s);
			if (gen == NULL) {
				printf("[ERROR] Plik nie istnieje lub nie jest plikiem generacji.\n");
				continue;
			} else {
				printf("Generacja wczytana pomyslnie.\n");
			}
			return gen;
		} else if (c == '2') {
			return loadGeneration1();
		} else if (c == '3') {
			return loadGeneration2();
		} else if (c == '4') {
			return NULL;
		} else {
			printf("Prosze podac cyfre od 1 do 4.\n");
			continue;
		}
	} while (0);
}

int programIteration(generation_t* gen) {	
	printf("\n");
	printf("Wybierz opcje:\n");
	printf("1. Przeprowadz generacje\n");
	printf("2. Zapisz aktualna generacje do pliku tekstowego\n");
	printf("3. Zapisz aktualna generacje do pliku graficznego\n");
	printf("4. Zakoncz\n");
	char c;
	do {
		scanf(" %c", &c);
		if (c == '1') {
			printf("Prosze podac liczbe generacji do przeprowadzenia: ");
			int n = -1;
			do {
				if (scanf("%i", &n) == 0 || n < 1) {
					printf("Prosze podac dodatnia liczbe.\n");
					continue;
				}
			} while (0);
			printf("Czy przeprowadzic animacje nastepnych generacji (y/n): ");
			do {
				scanf(" %c", &c);
				if (c == 'y' || c == 'Y') {
					draw(gen);
					for (int i = 0; i < n; i++) {
						msleep(SLEEPTIME);
						nextGeneration(gen);
						draw(gen);
					}
				} else if (c == 'n' || c == 'N') {
					for (int i = 0; i < n; i++)
						nextGeneration(gen);
					draw(gen);
				} else {
					printf("Prosze podac litere 'y' lub 'n'.\n");
					continue;
				}
			} while (0);
		} else if (c == '2') {	
			char* s = getStringInput("Prosze podac nazwe, ktora ma miec plik tekstowy: ");
			if (saveToFile(gen, s) == 1)
				printf("[ERROR] Wystapil problem przy zapisywaniu obrazka.\n");
			else
				printf("Obrazek zapisany pomyslnie.\n");
		} else if (c == '3') {
			char* s = getStringInput("Prosze podac nazwe, ktora ma miec plik graficzny: ");
			if (saveimg1(gen, s) == 1)
				printf("[ERROR] Wystapil problem przy zapisywaniu obrazka.\n");
			else
				printf("Obrazek zapisany pomyslnie.\n");
		} else if (c == '4') {
			return 1;
		} else {
			printf("Prosze podac cyfre od 1 do 4.\n");
			continue;
		}
	} while (0);
	return 0;
}

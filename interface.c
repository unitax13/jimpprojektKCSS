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
/* (funkcja wzieta z internetu) */
int msleep(long msec) {
    struct timespec ts;
    int res;
    
    if (msec < 0) {
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

/* Funkcje interfejsu programu */
generation_t* initGenerationInput() {
	char c;
	while (1) {
		printf("\n");
		printf("Wybierz opcje:\n");
		printf("1. Wczytaj generacje z pliku\n");
		printf("2. Wczytaj gotowa generacje nr 1\n");
		printf("3. Wczytaj gotowa generacje nr 2\n");
		printf("4. Zakoncz\n");
		scanf(" %c", &c);
		if (c == '1') {
			char* s = getStringInput("Prosze podac nazwe pliku: ");
			generation_t* gen = readFromFile(s);
			if (gen == NULL) {
				printf("[ERROR] Plik nie istnieje lub nie jest plikiem generacji.\n");
			} else {
				printf("Generacja wczytana pomyslnie.\n");
				return gen;
			}
			free(s);
		} else if (c == '2') {
			return loadGeneration1();
		} else if (c == '3') {
			return loadGeneration2();
		} else if (c == '4') {
			return NULL;
		} else {
			printf("Prosze podac cyfre od 1 do 4.\n");
		}
	}
}

int programIteration(generation_t* gen) {	
	printf("\n");
	printf("Wybierz opcje:\n");
	printf("1. Przeprowadz generacje\n");
	printf("2. Zapisz aktualna generacje do pliku tekstowego\n");
	printf("3. Zapisz aktualna generacje do pliku graficznego\n");
	printf("4. Zakoncz\n");
	char c;
	while (1) {
		scanf(" %c", &c);
		if (c == '1') {
			printf("Prosze podac liczbe generacji do przeprowadzenia: ");
			int n;
			char s[8];
			while (1) {
				scanf("%s", s);
				if (sscanf(s, "%i", &n) == 0 || n < 1)
					printf("Prosze podac dodatnia liczbe.\n");
				else
					break;
			}
			char a;
			printf("Czy przeprowadzic animacje nastepnych generacji (y/n): ");
			while (1) {
				scanf(" %c", &a);
				if (a == 'y' || a == 'Y' || a == 'n' || a == 'N')
					break;
				else
					printf("Prosze podac litere 'y' lub 'n'.\n");
			}
			char sv;
			printf("Czy zapisywac kolejne generacji do plikow graficznych? (y/n): ");
			while (1) {
				scanf(" %c", &sv);
				if (sv == 'y' || sv == 'Y' || sv == 'n' || sv == 'N')
					break;
				else
					printf("Prosze podac litere 'y' lub 'n'.\n");
			}
			if (sv == 'y' || sv == 'Y') {
				char is[12];
				sprintf(is, "%i", gen->generationNumber);
				saveimg1(gen, is);
			}
			system("clear");
			for (int i = 0; i < n; i++) {
				if (a == 'y' || a == 'Y') {
					draw(gen);
					msleep(SLEEPTIME);
					system("clear");
				}
				nextGeneration(gen);
				if (sv == 'y' || sv == 'Y') {
					char is[12];
					sprintf(is, "%i", gen->generationNumber);
					saveimg1(gen, is);
				}
				if (isGenerationDead(gen) == 1) {
			    		printf("Wszystkie komorki sa martwe!\n");	
       		                  	break;
                       		}
			}
			draw(gen);
			return 0;
		} else if (c == '2') {
			char* s = getStringInput("Prosze podac nazwe, ktora ma miec plik tekstowy: ");
			if (saveToFile(gen, s) == 1)
				printf("[ERROR] Wystapil problem przy zapisywaniu pliku.\n");
			else
				printf("Plik zapisany pomyslnie.\n");
			free(s);
			return 0;
		} else if (c == '3') {
			char* s = getStringInput("Prosze podac nazwe, ktora ma miec plik graficzny: ");
			if (saveimg1(gen, s) == 1)
				printf("[ERROR] Wystapil problem przy zapisywaniu obrazka.\n");
			else
				printf("Obrazek zapisany pomyslnie.\n");
			free(s);
			return 0;
		} else if (c == '4') {
			return 1;
		} else {
			printf("Prosze podac cyfre od 1 do 4.\n");
		}
	}
}

#ifndef GENERATION_H
#define GENERATION_H

typedef enum { DEAD = 0, DYING, BORN, ALIVE } cell_t;

typedef struct {
	cell_t** cells;
	int width, height;
	int generationNumber;
} generation_t;

/* Funkcja inicjalizujaca strukture generation_t */
generation_t* createNewGeneration(int width, int height);

/* Funkcja pomocnicza zwracajaca wartosc liczbowa
 * komorki na podanych wspolrzednych danej generacji
 * lub -1, jesli wspolrzedne wykraczaja poza wymiary */
int getCell(generation_t* gen, int x, int y);

/* Funkcja przeprowadzajaca kolejna generacje */
void nextGeneration(generation_t* gen);

/* Funkcja zwracajaca 1, gdy wszystkie komorki
 * w podanej generacji sa martwe lub 0
 * w przeciwnym razie*/
int isGenerationDead(generation_t* gen);

#endif

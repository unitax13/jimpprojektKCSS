#include <stdio.h>
#include <stdlib.h>

#include "saveimg.h"


int saveimg1(generation_t* gen, char* name, int width, int height)
{
    FILE *ouf = fopen (name,"wb");  //plik musi mieć rozszerzenie .pgm
    if (ouf == NULL) return 1;

    fprintf(ouf, "P1\n"); //tryb kodowania .pgm
    fprintf(ouf, "%d %d\n", width, height); //wymiary obrazka .pgm
    

    for (int x=0; x<gen->width; x++)
    {
        for(int y=0; y<gen->height; y++)
        {   int temp=0;
            if ( getCell(gen, y, x) == ALIVE) temp=1;
            fprintf(ouf, "%d", temp);
        }
    fprintf(ouf, "\n");
    }

    fclose(ouf);

    return 0;

}   
    


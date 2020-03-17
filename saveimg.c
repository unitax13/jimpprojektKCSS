#include <stdio.h>
#include <stdlib.h>

#include "saveimg.h"


int saveimg1(generation_t* gen, char* name)
{
    //  modul dodajacy rozszerzenie .pgm do nazwy pliku
    int namelen = 0;
    while (name[namelen]!='\0') namelen++;
    char finalname[namelen+4];
    for (int i=0; i<namelen; i++) finalname[i]=name[i];
    sprintf(finalname + namelen, ".pgm");

    FILE *ouf = fopen (finalname,"wb");  
    if (ouf == NULL) return 1;

    fprintf(ouf, "P1\n"); //tryb kodowania .pgm
    fprintf(ouf, "%d %d\n", gen->width,gen->height); //wymiary obrazka .pgm
    

    for (int y=0; y<gen->height; y++)
    {
        for(int x=0; x<gen->width; x++)
        { 
            int temp=0;
            if ( getCell(gen, x, y) == ALIVE ) temp=1;
            fprintf(ouf, "%d", temp);
        }
    fprintf(ouf, "\n");
    }

    fclose(ouf);

    return 0;

}   
    


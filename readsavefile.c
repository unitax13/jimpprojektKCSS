#include "readsavefile.h"
#include "generation.h"

#include <stdio.h>
#include <stdlib.h>

int saveToFile(generation_t* gen, char* name)
{
     /*   if (name == NULL) {
            FILE *ouf = fopen ("genstate", "w");                
        }
        else 
        {    
            FILE *ouf = fopen (name,"w");
        }
*/
//nie działa :(

    FILE *ouf = fopen ("genstate", "w");                

    //zapisywanie, takie jak w pliku draw

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
}

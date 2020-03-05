#include <stdio.h> //usun potem
#include <stdlib.h> //zeby dzialalo system("clear")
#include <unistd.h>
#include "generation.h" //usun potem
#include "draw.h"
#include "saveimg.h"

int main()
{
	generation_t* gen = createNewGeneration(10, 10);

    system("clear");
    draw(gen);
    sleep(1);

    system("clear");
    gen->cells[3][9] = ALIVE;
    gen->cells[2][9] = ALIVE;
    draw(gen);
    sleep(1);
    
    system("clear");
    gen->cells[3][8] = ALIVE;
    gen->cells[2][8] = ALIVE;
    gen->cells[4][9] = ALIVE;
    draw(gen);
    sleep(1);
    
    saveimg1(gen, "ostra nazwa");
	
    return 0;
}

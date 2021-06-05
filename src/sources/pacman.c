#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "../headers/beginning.h"
#include "../headers/clear.h"
#include "../headers/end.h"
#include "../headers/game.h"
#include "../headers/init_coord.h"
#include "../headers/keypress.h"
#include "../headers/move.h"
#include "../headers/records.h"
#include "../headers/show_grid.h"
#include "../headers/time.h"
#include "../headers/difficulties.h"
#include "../headers/size.h"


int main(int argc, char const **argv[]) {
    srand(time(NULL));
    FILE* file = NULL;
    char key[2], name[25];
    int nbstars = 20, lvl=0, nbfantomes = 0, score = 0;
    double temps;
    bool lose = false;
    clock_t start;

    introduction(name);
    if (introduction == NULL)
        printf("Saisie du pseudo incorrecte");
    lvl = level();
    nbfantomes = nbghost(&lvl);
    show_score(file, &lvl);
    int coordonnees[1 + nbfantomes + nbstars][2];
    if (coordonnees == NULL)
        printf("L'allocation tableau des coordonnees a echouee!\n");
    size_t tab = sizeof(coordonnees) / (sizeof(int)*2);

    start = beginning(coordonnees, &tab, &nbstars);
    
    while ((lose == false) && (score != 20)){
        keypress(key);
        if(keypress == NULL)
            printf("Saisie incorrecte");

        // Move pacman & ghost
        movement(&lvl, key, coordonnees, &nbfantomes);

        // Pacman meet star or ghost
        eat(coordonnees, &tab, &nbfantomes,  &score);
        dead(coordonnees, &nbfantomes, &lose);
        
        lose = chrono(start, &lose);

        show_grid(coordonnees, &tab, &nbstars);
        
    }
    temps = chrono_end(start);
    
    if(lvl != 1)
        final_score(&score, &temps);

    resultat(&lose);
    save_score(file, &lvl, &score, name);

    free(coordonnees);
    return 0;
}
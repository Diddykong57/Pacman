#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "beginning.h"
#include "clear.h"
#include "show_grid.h"
#include "init_coord.h"
#include "move.h"
#include "game.h"
#include "records.h"
#include "time.h"
#include "end.h"

#define NBETOILES 20
#define NBLIGNES 6
#define NBCOLONNES 10

struct personnage{
    int x;
    int y;
};


void keypress (char *key, int *nbfantomes);

int main(int argc, char const **argv[]) {
    int lvl=0;
    int nbfantomes = 2;
    char key[2];
    char name[25];
    int score = 0;
    bool lose = false;
    bool hard;
    clock_t start, end, middle;
    FILE* file = NULL;
    double temps;
    srand(time(NULL));

    introduction(name);
/*    lvl = level();
    printf("lvl : %d\n",lvl);
    //show_score(file, &lvl);
    int coordonnees[NBETOILES + nbfantomes][2];
    size_t tab = sizeof(coordonnees) / (sizeof(int)*2);

    if (coordonnees == NULL)
        printf("L'allocation tableau des coordonnees a echouee!\n");

    coord(coordonnees, &tab);
    
    affichageMatrice(coordonnees, &tab);
    start = clock();
    
    while ((lose == false) && (score != 20)){
        keypress(key, &nbfantomes);
        pacman(key, coordonnees);
        fantome(coordonnees, &nbfantomes);
        eat(coordonnees, &tab, &nbfantomes,  &score);
        dead(coordonnees, &nbfantomes, &lose);
        affichageMatrice(coordonnees, &tab);
        

        middle = clock();
        temps = ((double)middle - start) / CLOCKS_PER_SEC;
        timer(&temps, &lose);
        
    }
    end = clock();
    temps = ((double)end - start) / CLOCKS_PER_SEC;

    
    printf("\n\n       Votre temps est %.1f secondes.\n", temps);
    if(lvl != 1)
        final_score(&score, &temps);

    resultat(&lose);
    //save_score(file, &lvl, &score, name);

    free(coordonnees);*/
    return 0;
}
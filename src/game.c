#include <stdio.h>
#include <stdbool.h>
#include "game.h"

void eat(int coordonnees[][2], size_t *tab, int *nbfantomes, int *score){
    int i=0;
    for (i=*nbfantomes+1; i<*tab; i++){
        if((coordonnees[0][0] == coordonnees[i][0]) && (coordonnees[0][1] == coordonnees[i][1])){
            *score += 1;
            coordonnees[i][0] = -1;
            coordonnees[i][1] = -1;
        }
    }
    printf("    Votre score est : %d\n", *score);
}

void dead(int coordonnees[][2], int *nbfantomes, bool *lose){
    for (int i=1; i<=*nbfantomes; i++){
        if((coordonnees[0][0] == coordonnees[i][0]) && (coordonnees[0][1] == coordonnees[i][1]))
            *lose = true;
    }
}
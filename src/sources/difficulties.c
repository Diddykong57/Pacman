#include <stdio.h>
#include "../headers/difficulties.h"
#include "../headers/move.h"

int nbghost(int *lvl){
    int nb = 0;
    if ((*lvl == 3) || (*lvl == 5))
        nb = 3;
    else
        nb = 2;

    return nb;
}

void movement(int *lvl, char *key, int coordonnees[][2], int *nbfantomes){
    if (*lvl > 3){
        pacman(key, coordonnees);
        fantome(coordonnees, nbfantomes);
    } else {
        fantome(coordonnees, nbfantomes);
        pacman(key, coordonnees);
    }
}
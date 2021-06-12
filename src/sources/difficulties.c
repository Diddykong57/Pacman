#include <stdio.h>
#include "../headers/difficulties.h"
#include "../headers/move.h"
#include "../headers/keypress.h"

int nbghost(int *lvl){
    int nb = 0;
    if ((*lvl == 3) || (*lvl == 5))
        nb = 3;
    else
        nb = 2;

    return nb;
}

void movement(int *lvl, int coordonnees[][2], int *nbfantomes){
    char key[2];
    
    keypress(key);
    if(keypress == NULL)
        printf("Saisie incorrecte");
    
    if (*lvl > 3){
        pacman(key, coordonnees);
        fantome(coordonnees, nbfantomes);
    } else {
        fantome(coordonnees, nbfantomes);
        pacman(key, coordonnees);
    }
}
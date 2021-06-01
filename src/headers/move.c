#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "move.h"

#define NBETOILES 20
#define NBLIGNES 6
#define NBCOLONNES 10

void pacman(char *key, int coordonnees[][2]){
    if (strcmp(key,"q") == 0){
        if (coordonnees[0][1] - 1 >=0){
        coordonnees[0][1] -= 1;
        }
    } else if (strcmp(key,"d") == 0){
        if (coordonnees[0][1] + 1 < NBCOLONNES){
        coordonnees[0][1] += 1;
        }
    } else if (strcmp(key,"z") == 0){
        if (coordonnees[0][0] - 1 >=0){
        coordonnees[0][0] -= 1;
        }
    } else if (strcmp(key,"s") == 0){
        if (coordonnees[0][0] + 1 < NBLIGNES){
        coordonnees[0][0] += 1;
        }
    }
}

void fantome(int coordonnees[][2], int *nbfantomes){
    int i = 0;
    for (i=1; i<(*nbfantomes+1);i++){
        int move = rand()%2;
        if (coordonnees[i][move] > coordonnees[0][move])
            coordonnees[i][move] -= 1;
        else if (coordonnees[i][move] < coordonnees[0][move])
            coordonnees[i][move] += 1;
        else {
            if (move == 0){
                if (coordonnees[i][1] > coordonnees[0][1])
                    coordonnees[i][1] -= 1;
                else
                    coordonnees[i][1] += 1;
            } else {
                if (coordonnees[i][0] > coordonnees[0][0])
                    coordonnees[i][0] -= 1;
                else
                    coordonnees[i][0] += 1;
            }
        }
    } 
}
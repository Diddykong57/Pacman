#include <stdio.h>
#include <stdlib.h>
#include "../headers/init_coord.h"
#include "../headers/size.h"

struct personnage{
    int x;
    int y;
};

void coord(int coordonnees[][2], size_t *tab){
    int *size = size_grid();
    struct personnage perso[*tab];
    for (int i=0; i<(*tab); i++){
        if (i != 0){
            perso[i].x = rand()%(size[0]);
            perso[i].y = rand()%(size[1]);
        } else {
            perso[i].x = 4;
            perso[i].y = 5;
        }
        for (int j=0; j<i; j++){
            if (i != 0){
                if (((coordonnees[j][0] == perso[i].x) && (coordonnees[j][1] == perso[i].y)) || ((perso[i].x == coordonnees[0][0]) || (perso[i].y == coordonnees[0][1])))
                    i--;
            }
        }
        coordonnees[i][0] = perso[i].x;
        coordonnees[i][1] = perso[i].y;
    }
}
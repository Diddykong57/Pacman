#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/move.h"
#include "../headers/size.h"

void pacman(char *key, int coordonnees[][2]){
    int *size = size_grid();
    if (strcmp(key,"z") == 0){
        if (coordonnees[0][0] - 1 >=0){
        coordonnees[0][0] -= 1;
        }
    } else if (strcmp(key,"s") == 0){
        if (coordonnees[0][0] + 1 < size[0]){
        coordonnees[0][0] += 1;
        }
    } else if (strcmp(key,"q") == 0){
        if (coordonnees[0][1] - 1 >=0){
        coordonnees[0][1] -= 1;
        }
    } else if (strcmp(key,"d") == 0){
        if (coordonnees[0][1] + 1 < size[1]){
        coordonnees[0][1] += 1;
        }
    }
}

void fantome(int coordonnees[][2], int *nbfantomes){
    int ia = 0;
    for (int i=1; i<(*nbfantomes+1);i++){
        ia = rand()%2;

        if (ia == 0)
            move_ia(coordonnees, &i);
        else
            move_without_ia(coordonnees, &i);
    } 
}

void move_ia(int coordonnees[][2], int *i){
    int axe = rand()%2;
    // if coord_ghost > coord.ghost.z
    if (coordonnees[*i][axe] > coordonnees[0][axe])
        coordonnees[*i][axe] -= 1;
    // if coord_ghost < coord.ghost.z
    else if (coordonnees[*i][axe] < coordonnees[0][axe])
        coordonnees[*i][axe] += 1;
    // if coord_ghost = coord.ghost.z
    else {
        if (axe == 0){
            if (coordonnees[*i][1] > coordonnees[0][1])
                coordonnees[*i][1] -= 1;
            else
                coordonnees[*i][1] += 1;
        } else {
            if (coordonnees[*i][0] > coordonnees[0][0])
                coordonnees[*i][0] -= 1;
            else
                coordonnees[*i][0] += 1;
        }
    }
}

void move_without_ia(int coordonnees[][2], int *i){
    int *size = size_grid();
    int axe = rand()%2, sens = rand()%2;

    if (sens == 0){
        if(coordonnees[*i][axe] - 1 >= 0)
            coordonnees[*i][axe] -= 1;
    }
    else{
        if(axe == 0){
            if(coordonnees[*i][axe] < size[0] -1)
                coordonnees[*i][axe] += 1;
        } else {
            if(coordonnees[*i][axe] < size[1] -1)
                coordonnees[*i][axe] += 1;
        }
    }
}
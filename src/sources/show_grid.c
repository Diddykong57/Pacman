#include <stdio.h>
#include "../headers/show_grid.h"

#define NBETOILES 20
#define NBLIGNES 6
#define NBCOLONNES 10

void show_grid(int coordonnees[][2], size_t * tab, int *nbstar) {
    for (int i = 0; i < NBLIGNES; i++) {
        printf("   ");
        for (int j = 0; j < NBCOLONNES; j++) {
            printf("|   ");
            for (int k=0; k <= *tab; k++){
                if (k == 0){
                    if ((i == coordonnees[k][0]) && (j == coordonnees[k][1]))
                        printf("\b\b\b\b| C "); 
                }
                else if (k <= *tab - *nbstar -1){
                    if((i == coordonnees[k][0]) && (j == coordonnees[k][1]))
                        show_ghost(&i, &k, coordonnees);
                }
                else {
                    if ((i == coordonnees[k][0]) && (j == coordonnees[k][1]))
                        show_star(&k, coordonnees, tab, nbstar);
                }
            }
        }
        printf("|\n");
    }
}



void show_ghost(int *i, int *k, int coordonnees[][2]){
    printf("\b\b\b\b| X ");

    if((*i != 1) && (coordonnees[*k][0] == coordonnees[*k-1][0]) && (coordonnees[*k][1] == coordonnees[*k-1][1]))
        printf("\b\b\b\b|X X");
    if((coordonnees[0][0] == coordonnees[*k][0]) && (coordonnees[0][1] == coordonnees[*k][1]))
        printf("\b\b\b\b|XXX");
}

void show_star(int *k, int coordonnees[][2], size_t *tab, int *nbstar){
    printf("\b\b\b\b| * "); 

    for (int l = 0; l<= (*tab - *nbstar - 1); l++){
        if (l == 0){
            if ((coordonnees[l][0] == coordonnees[*k][0]) && (coordonnees[l][1] == coordonnees[*k][1]))
                printf("\b\b\b\b| C "); 
        } else {
            if ((coordonnees[l][0] == coordonnees[*k][0]) && (coordonnees[l][1] == coordonnees[*k][1]))
                printf("\b\b\b\b| X "); 
        }
    }
}  
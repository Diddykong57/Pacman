#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#include "../headers/beginning.h"
#include "../headers/clear.h"
#include "../headers/init_coord.h"
#include "../headers/show_grid.h"

void introduction(char *name){
    int ret;
    printf("\n     Entrer votre pseudo : ");
    ret = scanf("%25s", name);
    if(ret != 1)
        exit(1);

    clear_buffer();

    printf("\n     Bienvenue %s dans le jeu du pacman !\n", name);
    sleep(2);
    printf("\n     L'objectif est de recuperer 20 etoiles en 1 minute\n     Vous deplacerez votre personnage avec les touches ZQSD\n");
    sleep(2);
    printf("\n     Niveau 1 : Deux fantomes, pas de perte de points \n     Niveau 2 : Deux fantomes, perte de points / 15 secondes \n     Niveau 3 : Trois fantomes, perte de points / 15 secondes \n     Niveau 2 : Deux fantomes ameliores, perte de points / 15 secondes \n     Niveau 5 : ULTIME !\n");
}


int level(){
    bool reset = true;
    int lvl = 0, ret = 0;
    do{
        printf("\n     Saisir le niveau de difficulte : ");
        ret = scanf("%1d[1-5]",&lvl);
        clear_buffer();
        if(ret == 1){
            switch (lvl) {
                case 1 ... 5:
                    reset = false;
                    break;
                
                default:
                    printf("\n     Choisir parmi les niveaux de difficultes");
                    break;
            }
        } else
            printf("     Saisie incorrecte\n");
    } while (reset == true);
    printf("\n     Le chronometre debute a l'affichage du jeu\n     Que le meilleur gagne !\n\n");
    sleep(2);
    return lvl;
}

clock_t beginning(int coordonnees[][2], size_t *tab, int *nbstars){
    clock_t start = 0;
    coord(coordonnees, tab);
    show_grid(coordonnees, tab, nbstars);

    return start = clock();
}
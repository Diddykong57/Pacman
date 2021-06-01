#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "beginning.h"
#include "clear.h"

void introduction(char *name){
    int ret;
    printf("\n     Entrer votre pseudo : ");

    ret = scanf("%25s",name);
    clear_buffer();
    if(ret != 1)
        printf("Erreur lecture pseudo");

    printf("\n     Bienvenue %s dans le jeu du pacman !\n", name);
    sleep(2);
    printf("\n     L'objectif est de recuperer 20 etoiles en 1 minute\n     Vous deplacerez votre personnage avec les touches ZQSD\n");
    sleep(2);
    printf("\n     Niveau 1 : Deux fantomes, pas de perte de points \n     Niveau 2 : Deux fantomes, perte de points / 15 secondes \n     Niveau 3 : Trois fantomes, perte de points / 15 secondes \n");
}


int level(){
    bool reset = true;
    int lvl = 0;
    int ret;
    do{
        printf("\n     Saisir le niveau de difficulte : ");
        printf("\ndans lvl : %d\n",lvl);
        ret = scanf("%1d[0-9]",lvl);
        printf("\ndans lvl : %d\n",lvl);
        //clear_buffer();
        if(ret == 1){
            switch (lvl)
            {
            case 1 ... 3:
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
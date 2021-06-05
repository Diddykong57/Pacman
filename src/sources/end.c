#include <stdio.h>
#include <stdbool.h>
#include "../headers/end.h"


void final_score(int *score, double *temps){
    int a = *temps/15;
    *score -=  a;
    if (*score < 0){
        *score = 0;
    }
    printf("       Votre score final est : %d\n", *score);
}

void resultat(bool *lose){
    if (*lose == true)
        printf("       Dommage, vous avez perdu !");
    else
        printf("\n   (|___/)      Felicitations       (|___/)\n   (='.'=)        -   -   -         (='.'=)\n  ('')_('')    Vous avez gagne !   ('')_('')");
}
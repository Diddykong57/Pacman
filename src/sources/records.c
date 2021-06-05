#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/records.h"


void save_score(FILE *file, int *lvl, int *score, char *name){
    file = fopen("records.txt", "a");
    if (file == NULL)
        exit(1);

    fprintf(file,"%d %d %s \n", *lvl, *score, name);
    fclose(file);
}

void show_score(FILE *file, int *lvl){
    int niveau = 0, score = 0, score_bis = 0;
    char pseudo[30], pseudo_bis[30];
    
    file = fopen("records.txt", "r");
    if (file == NULL)
        exit(1);

    while(fscanf(file, "%d %d %s", &niveau, &score_bis, pseudo_bis) == 3){
        if(*lvl == niveau){
            if(score < score_bis){
                score = score_bis;
                strcpy(pseudo,pseudo_bis);
            }
        }
    }
    if (score == 0)
        printf("\n     -->  Niveau %d: Aucun record  <-- \n\n", *lvl);
    else
        printf("\n\n        -->  Niveau %d: Record detenu par %s  %d!  <-- \n\n", *lvl, pseudo, score);  
}
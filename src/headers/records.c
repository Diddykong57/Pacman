#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "records.h"


void save_score(FILE *file,int *lvl, int *score, char *name){
    file = fopen("records.txt", "a");
    if (file != NULL){
        fprintf(file,"%d %d %s \n", *lvl, *score, name);
        fclose(file);
    }
}

void show_score(FILE *file, int *lvl){
    char *fonction = NULL;
    char * endPtr;
    char *separateur ={" "};
    char niveau[2];
    char joueur[30];
    char raw[1];
    int score_bis;
    int score = 0;

    snprintf(niveau, 2, "%d",*lvl);
    
    file = fopen("records.txt", "r");
    if (file != NULL){
        // tant qu'il n'a pas parcouru l'intégralité du file
        while (fgets(raw, 2, file) != NULL){
            fonction = strtok(raw, separateur);
            printf("test* : %d\n",*fonction);
            printf("test : %d\n",fonction);
            printf("test& : %d\n",&fonction);
            printf("test* : %d\n",*raw);
            printf("test : %d\n",raw);
            printf("test& : %d\n",&raw);
                    
            // Sélection du niveau
            if (strcmp(fonction,niveau) == 0){
                fonction = strtok(NULL, separateur);
                score_bis = strtol(fonction, &endPtr ,10);
                if(*endPtr != '\0')
                    printf("Could not convert %s to long and leftover string is: %s", fonction, endPtr);
                printf("score : %d\n",score_bis);
                printf("score_fon : %s\n",fonction);
                printf("score_fon : %s\n",*fonction);

                // score max ?
                if (score_bis > score){
                    printf("score max trouve !\n");
                    score = score_bis;
                    fonction = strtok(NULL, separateur);
                    strcpy(joueur,fonction);
                }
            }
        }
        fclose(file);
    }

    if (score == 0)
        printf("\n     -->  Niveau %s: Aucun record  <-- \n\n", niveau);
    else
        printf("\n\n        -->  Niveau %s: Record detenu par %s  %d!  <-- \n\n", niveau, joueur, score);
}
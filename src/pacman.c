#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define NBETOILES 20
#define NBLIGNES 6
#define NBCOLONNES 10

struct personnage{
    int x;
    int y;
};

void clear_buffer(void);
void introduction(char *name);
void level(int *lvl);
void affichageMatrice(int coordonnees[][2], size_t *tab);
void coord(int coordonnees[][2], size_t *tab);
void keypress (char *key, int *nbfantomes);
void pacman(char *key, int coordonnees[][2]);
void fantome(int coordonnees[][2], int *nbfantomes);
void dead(int coordonnees[][2], int *nbfantomes, bool *lose);
void eat(int coordonnees[][2], size_t *tab, int *nbfantomes, int *score);
void timer(double *temps, bool *lose);
void save_score(FILE *file,int *lvl, int *score, char *name);
void show_score(FILE *file, int *lvl);
void final_score(int *score, double *temps);
void resultat(bool *lose);



int main(int argc, char const **argv[]) {
    int lvl=0;
    int nbfantomes = 2;
    char key[2];
    char name[25];
    int score = 0;
    bool lose = false;
    bool hard;
    clock_t start, end, middle;
    FILE* file = NULL;
    double temps;
    srand(time(NULL));

    //introduction(name);
    level(&lvl);
    show_score(file, &lvl);
    int coordonnees[NBETOILES + nbfantomes][2];
    size_t tab = sizeof(coordonnees) / (sizeof(int)*2);

    if (coordonnees == NULL)
        printf("L'allocation tableau des coordonnees a echouee!\n");

    coord(coordonnees, &tab);
    
    affichageMatrice(coordonnees, &tab);
    start = clock();
    
    while ((lose == false) && (score != 20)){
        keypress(key, &nbfantomes);
        pacman(key, coordonnees);
        fantome(coordonnees, &nbfantomes);
        eat(coordonnees, &tab, &nbfantomes,  &score);
        dead(coordonnees, &nbfantomes, &lose);
        affichageMatrice(coordonnees, &tab);
        

        middle = clock();
        temps = ((double)middle - start) / CLOCKS_PER_SEC;
        timer(&temps, &lose);
        
    }
    end = clock();
    temps = ((double)end - start) / CLOCKS_PER_SEC;

    
    printf("\n\n       Votre temps est %.1f secondes.\n", temps);
    if(lvl != 1)
        final_score(&score, &temps);

    resultat(&lose);
    save_score(file, &lvl, &score, name);

    free(coordonnees);
    return 0;
}


void clear_buffer(void){
    int c =0;
    while(c != '\n' && c != EOF)
        c = getchar();
}

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

void level(int *lvl){
    bool reset = true;
    int ret;
    size_t i = 1;
    do{
        printf("\n     Saisir le niveau de difficulte : ");
        ret = scanf("%1d[0-9]",lvl);
        clear_buffer();
        if(ret == 1){
            switch (*lvl)
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
}

void affichageMatrice(int coordonnees[][2], size_t * tab) {
    
    for (int i = 0; i < NBLIGNES; i++) {
        printf("   ");
        for (int j = 0; j < NBCOLONNES; j++) {
            printf("|   ");
            for (int k=0; k <= *tab; k++){
                if (k == 0){
                    if ((i == coordonnees[k][0]) && (j == coordonnees[k][1]))
                        printf("\b\b\b\b| C "); 
                }
                else if (k <= *tab - NBETOILES){
                    if((i == coordonnees[k][0]) && (j == coordonnees[k][1])){
                        printf("\b\b\b\b| X ");
                        if((i != 1) && (coordonnees[k][0] == coordonnees[k-1][0]) && (coordonnees[k][1] == coordonnees[k-1][1]))
                            printf("\b\b\b\b|X X");
                        if((coordonnees[0][0] == coordonnees[k][0]) && (coordonnees[0][1] == coordonnees[k][1]))
                            printf("\b\b\b\b|XXX");
                    }
                }
                else {
                    if ((i == coordonnees[k][0]) && (j == coordonnees[k][1])){
                        printf("\b\b\b\b| * "); 
                        for (int l = 0; l<= (*tab-NBETOILES); l++){
                            if (l == 0){
                                if ((coordonnees[l][0] == coordonnees[k][0]) && (coordonnees[l][1] == coordonnees[k][1]))
                                    printf("\b\b\b\b| C "); 
                            } else {
                                if ((coordonnees[l][0] == coordonnees[k][0]) && (coordonnees[l][1] == coordonnees[k][1]))
                                    printf("\b\b\b\b| X "); 
                            }
                        }
                    }
                }
            }
        }
        printf("|\n");
    }
}

void coord(int coordonnees[][2], size_t *tab){
    struct personnage perso[*tab];
    for (int i=0; i<(*tab); i++){
        if (i != 0){
            perso[i].x = rand()%(NBLIGNES);
            perso[i].y = rand()%(NBCOLONNES);
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


void keypress (char *key, int *nbfantomes){
    int size = 2;
    printf("     Ou veux-tu te deplacer ?  ");
    fgets(key,size,stdin);
    printf(" %s", key);

    clear_buffer();
}

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

void final_score(int *score, double *temps){
    int a = *temps/15;
    *score -=  a;
    if (*score < 0){
        *score = 0;
    }
    printf("       Votre score final est : %d\n", *score);
}

void resultat(bool *lose){
    if (*lose == true){
        printf("       Dommage, vous avez perdu !");
    } else {
        printf("\n   (|___/)      Felicitations       (|___/)");
        printf("\n   (='.'=)        -   -   -         (='.'=)");
        printf("\n  ('')_('')    Vous avez gagne !   ('')_('')");
    }
}

void eat(int coordonnees[][2], size_t *tab, int *nbfantomes, int *score){
    int i=0;
    for (i=*nbfantomes+1; i<*tab; i++){
        if((coordonnees[0][0] == coordonnees[i][0]) && (coordonnees[0][1] == coordonnees[i][1])){
            *score += 1;
            coordonnees[i][0] = -1;
            coordonnees[i][1] = -1;
        }
    }
    printf("    Votre score est : %d\n", *score);
}

void dead(int coordonnees[][2], int *nbfantomes, bool *lose){
    for (int i=1; i<=*nbfantomes; i++){
        if((coordonnees[0][0] == coordonnees[i][0]) && (coordonnees[0][1] == coordonnees[i][1]))
            *lose = true;
    }
}

void timer(double *temps, bool *lose){
    if (*temps > 60){
        *lose = true;
        printf("       Le temps est ecoule");
    }
}

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
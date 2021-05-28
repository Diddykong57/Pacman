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

void introduction(char *name);
void level(int *lvl);
void affichageMatrice(int coordonnees[][2], size_t *tab);
void coord(int coordonnees[][2], size_t *tab);
void keypress (char *key);
void pacman(char key[], int coordonnees[][2]);
void fantome(int coordonnees[][2], int *nbfantomes);
void dead(int coordonnees[][2], int *nbfantomes, bool *lose);
void resultat(bool *lose, double temps, int *lvl, int* score);
void eat(int coordonnees[][2], size_t *tab, int *nbfantomes, int *score);
void timer(double *temps, bool *lose);



int main(int argc, char const **argv[]) {
    int lvl=0;
    int nbfantomes = 2;
    char key;
    char name[25];
    int score = 0;
    bool lose = false;
    bool hard;
    clock_t start, end, middle;
    double temps;
    srand(time(NULL));

    //introduction(name);
    level(&lvl);
    int coordonnees[NBETOILES + nbfantomes][2];
    size_t tab = sizeof(coordonnees) / (sizeof(int)*2);

    if (coordonnees == NULL) 
        printf("L'allocation tableau des coordonnees a echouee!\n");
    

    coord(coordonnees, &tab);
    
    affichageMatrice(coordonnees, &tab);
    start = clock();
    
    while ((lose == false) && (score != 20)){
        keypress(&key);
        pacman(&key, coordonnees);
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
     
    resultat(&lose, temps, &lvl, &score);

    free(coordonnees);
    return 0;
}


void introduction(char *name){
    printf("\n     Entrer votre pseudo : ");
    scanf("%s",&name);
    printf("\n     Bienvenue %s dans le jeu du pacman !\n", &name);
    sleep(2);
    printf("\n     L'objectif est de recuperer 20 etoiles en 1 minute\n     Vous deplacerez votre personnage avec les touches ZQSD\n");
    sleep(2);
    printf("\n     Niveau 1 : Deux fantomes, pas de perte de points \n     Niveau 2 : Deux fantomes, perte de points / 15 secondes \n     Niveau 3 : Trois fantomes, perte de points / 15 secondes \n");
}

void level(int *lvl){
    bool reset = true;
    do{
        printf("\n     Saisir le niveau de difficulte : ");
        scanf("%1d",lvl);
        switch (*lvl)
        {
        case 1 ... 3:
            printf("\n     Le chronometre debute a l'affichage du jeu\n");
            printf("     Que le meilleur gagne !\n\n");
            reset = false;
            break;
        
        default:
            printf("\n     Choisir parmi les niveaux de difficultes");
            break;
        }
    } while (reset == true);
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


void keypress (char *key){
    bool reset = true;
    do{
        printf("     Ou veux-tu te deplacer ? ");
        scanf("%s", key);
        if ((strcmp(key,"z") == 0) || (strcmp(key,"q") == 0) || (strcmp(key,"s") == 0) || (strcmp(key,"d") == 0))
            reset = false;
        else
            printf("     Saisie incorrecte\n");
    } while (reset == true);
}

void pacman(char key[], int coordonnees[][2]){
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
    bool reset;  
    for (int i=1; i<(*nbfantomes+1);i++){
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

void resultat(bool *lose, double temps, int *lvl, int* score){
    printf("\n\n       Votre temps est %.1f secondes.\n", temps);
    if (*lvl != 1){
        for (int i=0;i<20;i++){
            if (temps > 15){
                temps -= 15;
                *score -=1;
            } else {
                break;
            }
        }
        if (*score < 0){
            *score = 0;
        }
        printf("       Votre score final est : %d\n", *score);
    }

    if (*lose == true){
        printf("       Dommage, vous avez perdu !");
    } else {
        printf("\n   (|___/)      Felicitations       (|___/)");
        printf("\n   (='.'=)        -   -   -         (='.'=)");
        printf("\n  ('')_('')    Vous avez gagne !   ('')_('')");
    }
    printf("\n\n");
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
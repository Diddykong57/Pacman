#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define NBLIGNES 6
#define NBCOLONNES 10

struct personnage{
    int x;
    int y;
};



void introduction(char *name);
int level();
void clear_buffer(void);
void final_score(int *score, double *temps);
void resultat(bool *lose);
void eat(int coordonnees[][2], size_t *tab, int *nbfantomes, int *score);
void dead(int coordonnees[][2], int *nbfantomes, bool *lose);
void coord(int coordonnees[][2], size_t *tab);
void pacman(char *key, int coordonnees[][2]);
void fantome(int coordonnees[][2], int *nbfantomes);
void save_score(FILE *file,int *lvl, int *score, char *name);
void show_score(FILE *file, int *lvl);
void show_grid(int coordonnees[][2], size_t * tab, int *nbstar);
void timer(double *temps, bool *lose);
char *keypress (char *key);
int nbghost(int *lvl);
bool chrono(clock_t start, bool *lose);
double chrono_end(clock_t start);
clock_t beginning(int coordonnees[][2], size_t *tab, int *nbstars);
void movement(int *lvl, char *key, int coordonnees[][2], int *nbfantomes);
void show_ghost(int *i, int *k, int coordonnees[][2]);
void show_star(int *k, int coordonnees[][2], size_t *tab, int *nbstar);
void move_ia(int coordonnees[][2], int *i);
void move_without_ia(int coordonnees[][2], int *i);



int main(int argc, char const **argv[]) {
    srand(time(NULL));
    FILE* file = NULL;
    char key[2], name[25];
    int nbstars = 20, lvl=0, nbfantomes = 0, score = 0;
    double temps;
    bool lose = false;
    clock_t start;

    introduction(name);
    if (introduction == NULL)
        printf("Saisie du pseudo incorrecte");
    lvl = level();
    nbfantomes = nbghost(&lvl);
    show_score(file, &lvl);
    int coordonnees[1 + nbfantomes + nbstars][2];
    if (coordonnees == NULL)
        printf("L'allocation tableau des coordonnees a echouee!\n");
    size_t tab = sizeof(coordonnees) / (sizeof(int)*2);

    start = beginning(coordonnees, &tab, &nbstars);
    
    while ((lose == false) && (score != 20)){
        keypress(key);
        if(keypress == NULL)
            printf("Saisie incorrecte");

        // Move pacman & ghost
        movement(&lvl, key, coordonnees, &nbfantomes);

        // Pacman meet star or ghost
        eat(coordonnees, &tab, &nbfantomes,  &score);
        dead(coordonnees, &nbfantomes, &lose);
        
        lose = chrono(start, &lose);

        show_grid(coordonnees, &tab, &nbstars);
        
    }
    temps = chrono_end(start);
    
    if(lvl != 1)
        final_score(&score, &temps);

    resultat(&lose);
    save_score(file, &lvl, &score, name);

    free(coordonnees);
    return 0;
}

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
    int lvl = 0;
    int ret;
    do{
        printf("\n     Saisir le niveau de difficulte : ");
        ret = scanf("%1d[1-5]",&lvl);
        clear_buffer();
        if(ret == 1){
            switch (lvl)
            {
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

void clear_buffer(void){
    int c =0;
    while(c != '\n' && c != EOF)
        c = getchar();
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
    if (*lose == true)
        printf("       Dommage, vous avez perdu !");
    else
        printf("\n   (|___/)      Felicitations       (|___/)\n   (='.'=)        -   -   -         (='.'=)\n  ('')_('')    Vous avez gagne !   ('')_('')");
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

char *keypress (char *key){
    char *data;

    printf("     Ou veux-tu te deplacer ?  ");
    data = fgets(key,2,stdin);
    clear_buffer();

    return data;
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
    int ia = 0;
    for (int i=1; i<(*nbfantomes+1);i++){
        ia = rand()%2;

        if (ia == 0)
            move_ia(coordonnees, &i);
        else
            move_without_ia(coordonnees, &i);
    } 
}

void save_score(FILE *file,int *lvl, int *score, char *name){
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

void timer(double *temps, bool *lose){
    if (*temps > 60){
        *lose = true;
        printf("       Le temps est ecoule\n");
    }
}

int nbghost(int *lvl){
    int nb = 0;
    if ((*lvl == 3) || (*lvl == 5))
        nb = 3;
    else
        nb = 2;

    return nb;
}

bool chrono(clock_t start, bool *lose){
    clock_t middle = 0;
    double temps;
    middle = clock();
    temps = ((double)middle - start) / CLOCKS_PER_SEC;
    timer(&temps, lose);

    return *lose;
}

double chrono_end(clock_t start){
    clock_t end = 0;
    double temps;

    end = clock();
    temps = ((double)end - start) / CLOCKS_PER_SEC;
    printf("\n\n       Votre temps est %.1f secondes.\n", temps);

    return temps;
}

clock_t beginning(int coordonnees[][2], size_t *tab, int *nbstars){
    clock_t start = 0;
    coord(coordonnees, tab);
    show_grid(coordonnees, tab, nbstars);

    return start = clock();
}

void movement(int *lvl, char *key, int coordonnees[][2], int *nbfantomes){
    if (*lvl > 3){
        pacman(key, coordonnees);
        fantome(coordonnees, nbfantomes);
    } else {
        fantome(coordonnees, nbfantomes);
        pacman(key, coordonnees);
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
    int axe = rand()%2;
    int sens = rand()%2;

    if (sens == 0){
        if(coordonnees[*i][axe] - 1 >= 0)
            coordonnees[*i][axe] -= 1;
    }
    else{
        if(axe == 0){
            if(coordonnees[*i][axe] < NBLIGNES -1)
                coordonnees[*i][axe] += 1;
        } else {
            if(coordonnees[*i][axe] < NBCOLONNES -1)
                coordonnees[*i][axe] += 1;
        }
    }
}
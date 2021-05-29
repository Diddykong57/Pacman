#ifndef GAME_H
#define GAME_H

void eat(int coordonnees[][2], size_t *tab, int *nbfantomes, int *score);
void dead(int coordonnees[][2], int *nbfantomes, bool *lose);

#endif
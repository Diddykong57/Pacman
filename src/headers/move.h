#ifndef MOVE_H
#define MOVE_H

void pacman(char *key, int coordonnees[][2]);
void fantome(int coordonnees[][2], int *nbfantomes);
void move_ia(int coordonnees[][2], int *i);
void move_without_ia(int coordonnees[][2], int *i);

#endif
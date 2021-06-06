#ifndef SHOW_GRID_H
#define SHOW_GRID_H

void show_grid(int coordonnees[][2], size_t * tab, int *nbstar);
void show_ghost(int *i, int *k, int coordonnees[][2]);
void show_star(int *k, int coordonnees[][2], size_t *tab, int *nbstar);

#endif
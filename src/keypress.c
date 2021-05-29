#include <stdio.h>
#include "keypress.h"
#include "clear.h"

void keypress (char *key, int *nbfantomes){
    int size = 2;
    printf("     Ou veux-tu te deplacer ?  ");
    fgets(key,size,stdin);
    printf(" %s", key);

    clear_buffer();
}
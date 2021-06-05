#include <stdio.h>
#include "../headers/keypress.h"
#include "../headers/clear.h"

char *keypress (char *key){
    char *data;

    printf("     Ou veux-tu te deplacer ?  ");
    data = fgets(key,2,stdin);
    clear_buffer();

    return data;
}
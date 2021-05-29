#include <stdio.h>
#include "clear.h"

void clear_buffer(void){
    int c =0;
    while(c != '\n' && c != EOF)
        c = getchar();
}
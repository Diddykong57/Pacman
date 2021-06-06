#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "../headers/time.h"

void timer(double *temps, bool *lose){
    if (*temps > 60){
        *lose = true;
        printf("       Le temps est ecoule\n");
    }
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
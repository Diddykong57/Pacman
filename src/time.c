#include <stdio.h>
#include <stdbool.h>
#include "time.h"

void timer(double *temps, bool *lose){
    if (*temps > 60){
        *lose = true;
        printf("       Le temps est ecoule");
    }
}
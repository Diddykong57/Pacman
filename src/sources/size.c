#include <stdio.h>
#include "../headers/size.h"

int * size_grid() {

   static int size[2];
   size[0] = 6;
   size[1] = 10;

   return size;
}
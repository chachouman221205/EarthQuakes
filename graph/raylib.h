#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "incidence_matrix.h"

#ifndef raylib
#define raylib



typedef struct Point{
    // int ID ?
    Node* node;

    int coordX;
    int coordY;

}Point;

typedef struct Way{
    // int ID ?
    Road* road;

}Way;



#endif

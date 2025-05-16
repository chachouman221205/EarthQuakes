#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"

#ifndef DRAW
#define DRAW


typedef struct Node Node;
typedef struct Road Road;
typedef struct Incidence_Matrix Incidence_Matrix;
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

void show_road(Road* road , int** sommets, Color col);
int** Coordonate_node(Incidence_Matrix* Incidence_Matrix , int weight , int high , int weightT , int highT);
void show(Incidence_Matrix* Incidence_Matrix , int** sommets);


#endif

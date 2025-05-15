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

void show_road(Road* road , int*** sommets);
int Coordonate_node(Matrix* matrix , int weight , int high , int weightT , int highT);
void show(Matrix* matrix , int*** sommets);


#endif

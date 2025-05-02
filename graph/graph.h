#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "incidence_matrix.h"

#ifndef GRAPH
#define GRAPH

typedef struct Road Road;
typedef struct Node{
    int ID;
    char type;

    unsigned int distance_to_origin;
    int max_capacity_to_origin;
    Road* towards_origin;
}Node;

typedef struct Road{
    // int ID ?
    Node* from;
    Node* to;

    int distance;
    bool usable;

    int current_capacity;
    int max_capacity;
}Road;

typedef struct Variables{
    int city_ids;
    int hospital_ids;
    int warehouse_ids;

}Variables;

void init_variables(Variables* variables);

void free_variables_struct(Variables* variables);

void print_road(Road* road);

#endif

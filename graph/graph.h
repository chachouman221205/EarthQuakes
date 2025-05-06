#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "incidence_matrix.h"

#ifndef GRAPH
#define GRAPH

typedef struct Road Road;
typedef struct Matrix Matrix;

typedef struct Node{
    int ID;
    char type;

    bool explored;
    
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

Variables* init_variables();

void free_variables_struct(Variables* variables);

Road* init_road(Node* from, Node* to, int distance, bool usable, int max_capacity);
void free_road(Road* r);
void print_road(Road* road);
void print_roads(Matrix* matrix);

Node* init_node(Variables* variables, char type);
void free_node(Node* n);

void print_damage(Matrix* matrix);

void print_all_path_from_origin(Matrix* matrix);
void print_unaccessible_nodes(Matrix* matrix);
void reset_exploration(Matrix* matrix);
#endif

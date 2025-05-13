#ifndef GRAPH
#define GRAPH

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct Road Road;
typedef struct Matrix Matrix;

typedef struct Node {
    int ID;
    char type;

    bool explored;
    
    unsigned int distance_to_origin;
    int max_capacity_to_origin;
    int connections_in;
    int connections_out;
    Road* towards_origin;

    int current_capacity[5];
    // {Provisions;médicaments;médecins;ouvriers;matériaux}
    bool Is_repared;

} Node;

typedef struct Road {
    // int ID ?
    Node* from;
    Node* to;

    unsigned int distance;
    bool usable;
    bool to_secure;
    bool is_created;

    int current_capacity;
    int max_capacity;
    //int future_occupation;
} Road;

typedef struct Variables {
    int city_ids;
    int hospital_ids;
    int warehouse_ids;
} Variables;

#include "incidence_matrix.h"



Variables* init_variables();

void free_variables_struct(Variables* variables);

Road* init_road(Node* from, Node* to, int distance, bool usable, int max_capacity);
void free_road(Road* r);
void print_road(Road* road);
void print_roads(Matrix* matrix);

Node* init_node(Variables* variables, char type);
void free_node(Node* n);

void print_damage(Matrix* matrix);

bool is_usable(Road* road);
void explore_all_nodes_width(Matrix* matrix);

void print_all_path_from_origin(Matrix* matrix);
void print_unaccessible_nodes(Matrix* matrix);
void reset_exploration(Matrix* matrix);

void print_road_to_secure(Road* road);
void print_roads_to_secure(Matrix* matrix);

void print_road_created(Road* road);
void print_roads_created(Matrix* matrix);

#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "incidence_matrix.h"

typedef struct Node{
    int ID;
    char type;

    int distance_to_origin;
    int max_capacity_to_origin;
    Road* towards_origin;
}Node;

typedef struct Road{
    // int ID ?
    Node* from;
    Node* to;

    bool direction;
    int distance;
    bool state;

    int current_capacity;
    int max_capacity;
}Road;

typedef struct Variables{
    int* node_type_ids;

}Variables;

void init_variables(Variables* variables);

void free_variables_struct(Variables* variables);

void print_road(Road* road);

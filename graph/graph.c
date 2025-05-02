#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "graph.h"

Variables* init_variables(){
    Variables* variables = malloc(1*sizeof(Variables));
    if(variables == NULL){
        fprintf(stderr, "\033[1;31mAllocation ERROR in \"init_data\"\033[1;0m\n");
        exit(1);
    }

    variables->city_ids = 0;
    variables->hospital_ids = 0;
    variables->warehouse_ids = 0;

    return variables;
}

void free_variables_struct(Variables* variables){
    free(variables);
}

/*
    void graph_exploration(Matrix* matrix){
        for(int line = 0; line < matrix->size; line++){
            for(int column = 0; column < matrix->size; column++){
                pass();
            }
        }
    }
*/

Road* init_road(Node* from, Node* to, int distance, bool usable, int max_capacity) {
    Road* r = malloc(sizeof(Road));
    r->from = from;
    r->to = to;
    r->distance = distance;
    r->usable = usable;
    r->current_capacity = max_capacity;
    r->max_capacity = max_capacity;

    return r;
}

void free_road(Road* r) {
    free(r);
}

void print_road(Road* road){
    printf("Road from %s%d to %s%d :\n",
        (road->from->type == 'C')? "City" : ((road->from->type == 'H')? "Hospital" : "Warehouse"),
        road->from->ID,
        (road->from->type == 'C')? "City" : ((road->from->type == 'H')? "Hospital" : "Warehouse"),
        road->from->ID);
    printf("  -> State : %s\n", 
        (road->usable)? "\033[1;31mDestroyed\033[0m" : "\033[1;32mAccessible\033[0m");
    printf("  -> Current capacity : %d\n", road->current_capacity);
    printf("  -> Maximum capacity : %d\n", road->max_capacity);
    printf("\n");
}

void print_roads(Matrix* matrix){
    for(int line = 0; line < matrix->size; line++){
        for(int column = 0; column < matrix->size; column++){
            if(matrix->grid[line][column] != NULL){
                print_road(matrix->grid[line][column]);
            }
        }
    }
}

Node* init_node(Variables* variables, char type) {
    Node* n = malloc(sizeof(Node));
    switch (type) {
        case 'C':
            n->ID = variables->city_ids;
            break;
        case 'H':
            n->ID = variables->hospital_ids;
            break;
        case 'W':
            n->ID = variables->warehouse_ids;
            break;
    }

    n->distance_to_origin = -1;

    return n;
}

void free_node(Node* n) {
    free(n);
}

void print_damage(Matrix* matrix){
    int accessible = 0, destroyed = 0;
    for(int line = 0; line < matrix->size; line++){
        for(int column = 0; column < matrix->size; column++){
            if(matrix->grid[line][column] != NULL){
                (matrix->grid[line][column]->usable)? destroyed++ : accessible++;
            }
        }
    }
    printf("There were %d accessible roads before the earthquake\n", destroyed + accessible);
    printf("There are now %d accessible roads and %d destroyed roads\n", accessible, destroyed);
}

/* nassim : 
- fonction d'exloration qui print les chemins
- qui me rempli un tableau de taille matrix->size :
    -> 1 si tu as exploré le sommet, touche pas sinon (0)

(option) tu peux remplir la distance from origin ici
*/
void print_all_path_from_origin(Matrix* matrix, int* tab);

void print_unaccessible_nodes(Matrix* matrix, int* tab){
    printf("The unaccessible nodes are :\n  -> ");
    for(int i = 0; i < matrix->size; i++){
        if(tab[i] == 0){
            printf("%c%d ", matrix->nodes[i]->type, matrix->nodes[i]->ID);
        }
    }
    printf("\n");
}

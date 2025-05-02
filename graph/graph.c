#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "graph.h"

void init_variables(Variables* variables){
    variables->node_type_ids = calloc(3, sizeof(int));
    if(variables->node_type_ids == NULL){
        printf("\033[1;31mAllocation ERROR in \"init_data\"\033[1;0m\n");
        exit(1);
    }
}

void free_variables_struct(Variables* variables){
    free(variables->node_type_ids);

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

void print_road(Road* road){
    printf("Road from %s%d to %s%d :\n",
        (road->from->type == 'C')? "City" : ((road->from->type == 'H')? "Hospital" : "Warehouse"),
        road->from->ID,
        (road->from->type == 'C')? "City" : ((road->from->type == 'H')? "Hospital" : "Warehouse"),
        road->from->ID);
    printf("  -> State : %s\n", 
        (road->state)? "\033[1;31mDestroyed\033[0m" : "\033[1;32mAccessible\033[0m");
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

void print_damage(Matrix* matrix){
    int accessible = 0, destroyed = 0;
    for(int line = 0; line < matrix->size; line++){
        for(int column = 0; column < matrix->size; column++){
            if(matrix->grid[line][column] != NULL){
                (matrix->grid[line][column]->state)? destroyed++ : accessible++;
            }
        }
    }
    printf("There were %d roads before the earthquake.\n", destroyed + accessible);
    printf("There are now %d accessible roads and %d destroyed roads\n", accessible, destroyed);
}

void print_unaccessible_nodes(Matrix* matrix){
    pass();
}

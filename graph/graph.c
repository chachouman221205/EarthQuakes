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

void print_unaccessible_nodes(Matrix* matrix){
    // inverse l'ordre de recherche pour voir si un noeud n'a aucune route en état qui va vers lui
    bool has_accessible_roads;
    printf("The now unaccessible roads are :\n  -> ");
    for(int column = 0; column < matrix->size; column++){
        has_accessible_roads = false;
        for(int line = 0; line < matrix->size; line++){
            if(matrix->grid[line][column] != NULL){
                if(matrix->grid[line][column]->state == true){
                    has_accessible_roads = true;
                }
            }
        }
        if(has_accessible_roads == false){
            printf("  -> %d ", column);
        }
    }
    printf("\n");
}

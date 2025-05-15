#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "graph.h"
#include "linked_list.h"


char* find_file(char* filename){
    FILE *f;
    int name_id = 1;

    // Trouver un nom de fichier qui n'existe pas encore
    do {
        sprintf(filename, "test/gen_files/gen_graph%d.txt", name_id);
        f = fopen(filename, "r");
        if(f != NULL) {
            fclose(f);
            name_id++;
        }
    } while(f != NULL);

    sprintf(filename, "test/gen_files/gen_graph%d.txt", --name_id);
    printf("\033[1;35mUsing :\033[0m %s\n\n", filename);
    return filename;
}


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
    void graph_exploration(Incidence_Matrix* incidence_matrix){
        for(int line = 0; line < incidence_matrix->size; line++){
            for(int column = 0; column < incidence_matrix->size; column++){
                pass();
            }
        }
    }
*/

Road* init_road(Node* from, Node* to, int distance, bool usable, int max_capacity) {
    Road* r = malloc(sizeof(Road));
    if(r == NULL){
        printf("\033[0;31mAllocation ERROR in \"init_road\"\033[0;0m\n");
        exit(1);
    }
    r->from = from;
    from->connections_out++;
    r->to = to;
    to->connections_in++;
    r->distance = distance;
    r->usable = usable;
    r->current_capacity = max_capacity;
    r->max_capacity = max_capacity;
    r->to_secure = false;
    r->is_created = false;

    return r;
}

void free_road(Road* r) {
    free(r);
}

void print_road(Road* road){
    char type1[20], type2[20];
    switch (road->from->type) {
        case 'C':
            strcpy(type1, "City");
            break;
        case 'H':
            strcpy(type1, "Hospital");
            break;
        case 'W':
            strcpy(type1, "Warehouse");
            break;
        default:
            strcpy(type1, "Unknown");
    }
    switch (road->to->type) {
        case 'C':
            strcpy(type2, "City");
            break;
        case 'H':
            strcpy(type2, "Hospital");
            break;
        case 'W':
            strcpy(type2, "Warehouse");
            break;
        default:
            strcpy(type2, "Unknown");
    }
    printf("Road from \033[0;36m%s%d\033[0m to \033[0;36m%s%d\033[0m :\n", 
        type1, road->from->ID, type2, road->to->ID);
    printf("  ⤷ State : %s\n", 
        (road->usable)? "\033[1;32mAccessible\033[0m" : "\033[1;31mDestroyed\033[0m");
    (road->current_capacity != 0)?
        printf("  ⤷ Current capacity : %4d\n", road->current_capacity) :
        printf("  ⤷ Current capacity :    \033[1;31m0\033[0m\n");
    printf("  ⤷ Maximum capacity : %4d\n", road->max_capacity);
    printf("\n");
}

void print_roads(Incidence_Matrix* incidence_matrix){
    for(int line = 0; line < incidence_matrix->size; line++){
        for(int column = 0; column < incidence_matrix->size; column++){
            if(incidence_matrix->grid[line][column] != NULL){
                print_road(incidence_matrix->grid[line][column]);
            }
        }
    }
}

Node* init_node(Variables* variables, char type) {
    Node* n = malloc(sizeof(Node));
    if(n == NULL){
        printf("\033[0;31mAllocation ERROR in \"init_node\"\033[0;0m\n");
        exit(1);
    }
    switch (type) {
        case 'C':
            n->ID = variables->city_ids++;
            break;
        case 'H':
            n->ID = variables->hospital_ids++;
            break;
        case 'W':
            n->ID = variables->warehouse_ids++;
            break;
    }

    n->type = type;

    n->distance_to_origin = -1;
    n->towards_origin = NULL;
    n->explored = 0;
    n->connections_in = 0;
    n->connections_out = 0;
    n->Is_repared = 0;
    for (int i=0 ; i < 5 ; i++){
        n->current_capacity[i] = 0;
    }

    return n;
}

void free_node(Node* n) {
    free(n);
}

void print_damage(Incidence_Matrix* incidence_matrix){
    int accessible = 0, destroyed = 0;
    for(int line = 0; line < incidence_matrix->size; line++){
        for(int column = 0; column < incidence_matrix->size; column++){
            if(incidence_matrix->grid[line][column] != NULL){
                (incidence_matrix->grid[line][column]->usable)? accessible++ : destroyed++;
            }
        }
    }
    printf("There were \033[1;32m%d accessible\033[0m roads before the earthquake\n", 
        destroyed + accessible);
    printf("There are now \033[1;32m%d accessible\033[0m roads and ", accessible);
    printf("\033[1;31m%d destroyed\033[0m roads\n\n", destroyed);
}


void print_all_path_from_origin(Incidence_Matrix* incidence_matrix) {
    explore_all_nodes_width(incidence_matrix);
    printf("The \033[1;32maccessible\033[0m nodes are :\n  ⤷ ");
    for(int i = 0; i < incidence_matrix->size; i++){
        if(incidence_matrix->nodes[i]->explored == true){
            printf("%c%d ", incidence_matrix->nodes[i]->type, incidence_matrix->nodes[i]->ID);
        }
    }
    printf("\n");
    reset_exploration(incidence_matrix);
}

void reset_exploration(Incidence_Matrix* incidence_matrix) {
    for (int i = 0; i < incidence_matrix->size; i++) {
        incidence_matrix->nodes[i]->explored = false;
    }
}

bool is_usable(Road* road) {
    if (road != NULL) {
        return road->usable && (road->current_capacity > 0);
    }
    return false;
}

void explore_all_nodes_width(Incidence_Matrix* incidence_matrix) {
    ListHead* node_queue = ListInit();
    ListQueue(node_queue, 0);
    incidence_matrix->nodes[0]->explored = true;
    int current_node;
    // tant qu'il reste des noeuds à explorer
    while (node_queue->length > 0) {
        current_node = ListPop(node_queue, 0);
        // pour chaque voisin
        for (int i = 0; i < incidence_matrix->size; i++) {
            // qui existe et qui n'est pas exploré
            if (is_usable(incidence_matrix->grid[current_node][i]) && incidence_matrix->grid[current_node][i]->to->explored == false) {
                ListQueue(node_queue, i);
                incidence_matrix->nodes[i]->explored = true;
            }
        }
    }
    ListFree(node_queue);
}

void print_unaccessible_nodes(Incidence_Matrix* incidence_matrix){
    explore_all_nodes_width(incidence_matrix);
    printf("The \033[1;31munnaccessible\033[0m nodes are :\n  ⤷ ");
    for(int i = 0; i < incidence_matrix->size; i++){
        if(incidence_matrix->nodes[i]->explored == false){
            printf("%c%d ", incidence_matrix->nodes[i]->type, incidence_matrix->nodes[i]->ID);
        }
    }
    printf("\n");
    reset_exploration(incidence_matrix);
}

void print_road_to_secure(Road* road){
    char type1[20], type2[20];
    switch (road->from->type) {
        case 'C':
            strcpy(type1, "City");
            break;
        case 'H':
            strcpy(type1, "Hospital");
            break;
        case 'W':
            strcpy(type1, "Warehouse");
            break;
        default:
            strcpy(type1, "Unknown");
    }
    switch (road->to->type) {
        case 'C':
            strcpy(type2, "City");
            break;
        case 'H':
            strcpy(type2, "Hospital");
            break;
        case 'W':
            strcpy(type2, "Warehouse");
            break;
        default:
            strcpy(type2, "Unknown");
    }
    if(road->to_secure == true){
        printf("Road \033[0;36m%s%d\033[0m to \033[0;36m%s%d\033[0m\n", 
            type1, road->from->ID, type2, road->to->ID);
    }
}

void print_roads_to_secure(Incidence_Matrix* incidence_matrix){
    int count = 0;
    for(int line = 0; line < incidence_matrix->size; line++){
        for(int column = 0; column < incidence_matrix->size; column++){
            if(incidence_matrix->grid[line][column] != NULL && incidence_matrix->grid[line][column]->to_secure){
                print_road_to_secure(incidence_matrix->grid[line][column]);
                count++;
            }
        }
    }
    printf("\033[0;36m%d\033[0m Roads have been marked as critical to secure\n", count);
}

void print_road_created(Road* road){
    char type1[20], type2[20];
    switch (road->from->type) {
        case 'C':
            strcpy(type1, "City");
            break;
        case 'H':
            strcpy(type1, "Hospital");
            break;
        case 'W':
            strcpy(type1, "Warehouse");
            break;
        default:
            strcpy(type1, "Unknown");
    }
    switch (road->to->type) {
        case 'C':
            strcpy(type2, "City");
            break;
        case 'H':
            strcpy(type2, "Hospital");
            break;
        case 'W':
            strcpy(type2, "Warehouse");
            break;
        default:
            strcpy(type2, "Unknown");
    }
    if(road->is_created == true){
        printf("Road created from \033[0;36m%s%d\033[0m to \033[0;36m%s%d\033[0m\n", 
            type1, road->from->ID, type2, road->to->ID);
    }
}

void print_roads_created(Incidence_Matrix* incidence_matrix){
    for(int line = 0; line < incidence_matrix->size; line++){
        for(int column = 0; column < incidence_matrix->size; column++){
            if(incidence_matrix->grid[line][column] != NULL){
                print_road_created(incidence_matrix->grid[line][column]);
            }
        }
    }
}



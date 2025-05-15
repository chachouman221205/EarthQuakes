#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "graph.h"
#include "linked_list.h"
#include "raylib.h"
#include <time.h>

Way* init_way(Road e) {
    Way* w = malloc(sizeof(Way));
    if(w == NULL){
        printf("\033[0;31mAllocation ERROR in \"init_road\"\033[0;0m\n");
        exit(1);
    }
    w->road = &e;
    return w;
}

void free_way(Way* r) {
    free(r);
}

/*void print_road(Road* road){
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
}*/

/*void print_roads(Matrix* matrix){
    for(int line = 0; line < matrix->size; line++){
        for(int column = 0; column < matrix->size; column++){
            if(matrix->grid[line][column] != NULL){
                print_road(matrix->grid[line][column]);
            }
        }
    }
}*/

void show_road(Road* road , int*** sommets){
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
        DrawLine(sommets[road->from->ID][0], sommets[road->from->ID][1],sommets[road->to->ID][0], sommets[road->to->ID][1], YELLOW);
    }
    else if(road->to_secure == true){
        DrawLine(sommets[road->from->ID][0], sommets[road->from->ID][1],sommets[road->to->ID][0], sommets[road->to->ID][1], BLUE);
    }
    else if(road->usable == false){
        DrawLine(sommets[road->from->ID][0], sommets[road->from->ID][1],sommets[road->to->ID][0], sommets[road->to->ID][1], RED);
    }
    else(road->is_created == true){
        DrawLine(sommets[road->from->ID][0], sommets[road->from->ID][1],sommets[road->to->ID][0], sommets[road->to->ID][1], GREEN);
    }
}

int Coordonate_node(Matrix* matrix , int weight , int high , int weightT , int highT){
    srand(time(NULL));
    int Coords[matrix->size][2];
    for ( int i = 0 ; i < matrix->size ; i++){
            Coords[i][0] = (weightT - weight)  + (rand() % weight);
            Coords[i][1] = (highT - high)  + (rand() % high);   
        }
    return Coords;
} 

void show(Matrix* matrix , int*** sommets){
    for(int line = 0; line < matrix->size; line++){
        for(int column = 0; column < matrix->size; column++){
            if(matrix->grid[line][column] != NULL){
                show_road(matrix->grid[line][column] , sommets);
            }
        }
    }
    for (int k = 0 ; k < matrix->size ; k++){
            DrawCircle(sommets[k][0], sommets[k][1], 3, VIOLET);
            DrawText("node", sommets[k][0] - 15 ,sommets[k][1] + 5, 6, VIOLET);
    }
}


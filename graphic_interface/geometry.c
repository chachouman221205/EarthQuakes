#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../graph/graph.h"
#include "geometry.h"
#include "raylib.h"
#include "raylib_utils.h"

#define TOOL_TIP_COLOR ((Color) {0,0,0,150})

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

/*void print_roads(Incidence_Matrix* Incidence_Matrix){
    for(int line = 0; line < Incidence_Matrix->size; line++){
        for(int column = 0; column < Incidence_Matrix->size; column++){
            if(Incidence_Matrix->grid[line][column] != NULL){
                print_road(Incidence_Matrix->grid[line][column]);
            }
        }
    }
}*/

void show_road(Road* road , int** sommets, Color col){
    Vector2 start = (Vector2) {sommets[road->from->ID][0], sommets[road->from->ID][1]};
    Vector2 end = (Vector2) {sommets[road->to->ID][0], sommets[road->to->ID][1]};
    float thick = 2;
    float arrow_head_size = 10;
    bool hover = CheckCollisionPointLine(GetMousePosition(), start, end, 5);

    if (hover) {
        col = brightness(col, 0.7);
        thick = 5;
        arrow_head_size = 15;
    }



    DrawLineEx(start, end, thick, col);

    // vecteur qui permet de dessiner les détails des flèches
    Vector2 sized = scale((Vector2) {sommets[road->to->ID][0]-sommets[road->from->ID][0], sommets[road->to->ID][1]-sommets[road->from->ID][1]}, arrow_head_size);
    Vector2 rotate1 = rotate(sized, 10);
    Vector2 rotate2 = rotate(sized, -10);

    DrawLineEx(end, (Vector2) {sommets[road->to->ID][0] + rotate1.x, sommets[road->to->ID][1] + rotate1.y}, thick, col);
    DrawLineEx(end, (Vector2) {sommets[road->to->ID][0] + rotate2.x, sommets[road->to->ID][1] + rotate2.y}, thick, col);

    return;
}

int** Coordonate_node(Incidence_Matrix* incidence_matrix , int width , int height , int widthT , int heightT){
    srand(incidence_matrix->size);
    int** Coords = malloc(incidence_matrix->size * sizeof(int*));
    for (int i = 0; i < incidence_matrix->size; i++) {
        Coords[i] = malloc(2*sizeof(int));
    }

    for ( int i = 0 ; i < incidence_matrix->size ; i++){
            Coords[i][0] = (widthT - width)  + (rand() % width);
            Coords[i][1] = (heightT - height)  + (rand() % height);
        }
    return Coords;
}

void show_path(int** sommets, ListHead* path, Color col) {
    ListNode* ptr = path->next;
    while (ptr != NULL && ptr->next != NULL) {
        DrawLine(sommets[ptr->data][0], sommets[ptr->data][1], sommets[ptr->next->data][0], sommets[ptr->next->data][1], col);
        ptr = ptr->next;
    }
}

void show_node_tool_tip(Incidence_Matrix* incidence_matrix, int** sommets, int k) {
    int tool_tip_x = sommets[k][0];
    int tool_tip_y = sommets[k][1];
    char type[30];
    switch (incidence_matrix->nodes[k]->type) {
        case 'C':
            strcpy(type, "City");
            break;
        case 'H':
            strcpy(type, "Hospital");
            break;
        case 'W':
            strcpy(type, "Warehouse");
            break;
        default:
            strcpy(type, "Unknown");
    }
    sprintf(type + strlen(type), " %d", incidence_matrix->nodes[k]->ID);

    show_path(sommets, find_path_to(incidence_matrix, k), BLACK);
    DrawRectangle(tool_tip_x, tool_tip_y, 70, 100, TOOL_TIP_COLOR);
    // Afficher le texte décrivant chaque sommet

    DrawText(type, tool_tip_x+5, tool_tip_y+10, 20, incidence_matrix->nodes[k]->accessible ? GREEN : RED);
}

void show_node(Incidence_Matrix* incidence_matrix, int** sommets, int k) {
    char type[30];
    switch (incidence_matrix->nodes[k]->type) {
        case 'C':
            strcpy(type, "City");
            break;
        case 'H':
            strcpy(type, "Hospital");
            break;
        case 'W':
            strcpy(type, "Warehouse");
            break;
        default:
            strcpy(type, "Unknown");
    }
    sprintf(type + strlen(type), " %d", incidence_matrix->nodes[k]->ID);
    Vector2 center = {sommets[k][0], sommets[k][1]};
    DrawCircle(sommets[k][0], sommets[k][1], 3, incidence_matrix->nodes[k]->accessible ? GREEN : RED);
    DrawText(type, sommets[k][0] - 15 ,sommets[k][1] + 5, 6, VIOLET);

    if (CheckCollisionPointCircle(GetMousePosition(), center, 10)) {
        show_node_tool_tip(incidence_matrix, sommets, k);
    }
}

void show(Incidence_Matrix* incidence_matrix , int** sommets){
    for(int line = 0; line < incidence_matrix->size; line++){
        for(int column = 0; column < incidence_matrix->size; column++){
            if(incidence_matrix->grid[line][column] != NULL){
                if(incidence_matrix->grid[line][column]->is_created == true){
                    show_road(incidence_matrix->grid[line][column], sommets, YELLOW);
                }
                else if(incidence_matrix->grid[line][column]->to_secure == true){
                    show_road(incidence_matrix->grid[line][column], sommets, BLUE);
                }
                else if(incidence_matrix->grid[line][column]->usable == false){
                    show_road(incidence_matrix->grid[line][column], sommets, RED);
                }
                else {
                    show_road(incidence_matrix->grid[line][column], sommets, GREEN);
                }
            }
        }
    }
    for (int k = 0 ; k < incidence_matrix->size ; k++){
        show_node(incidence_matrix, sommets, k);
    }
}


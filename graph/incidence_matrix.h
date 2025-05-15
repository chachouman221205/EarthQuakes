#ifndef INCIDENCE_MATRIX
#define INCIDENCE_MATRIX

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "linked_list.h"

typedef struct Node Node;
typedef struct Road Road;
typedef struct Variables Variables;
typedef struct Incidence_Matrix {
    int size;
    Node** nodes;
    Road*** grid;
} Incidence_Matrix;


Incidence_Matrix* init_empty_incidence_matrix(int size);
Incidence_Matrix* init_incidence_matrix_from_file(Variables* variables, char* fp);

void free_incidence_matrix_content(Incidence_Matrix* incidence_matrix);
void free_incidence_matrix(Incidence_Matrix* incidence_matrix);

int calculate_origin_path(Incidence_Matrix* incidence_matrix, int node, int* distance);
void calculate_origin_distances(Incidence_Matrix* incidence_matrix);
ListHead* find_path_to(Incidence_Matrix* incidence_matrix, int node);
void print_path(Incidence_Matrix* incidence_matrix, ListHead* path, int* length);

void multiply_incidence_matrix(Incidence_Matrix* incidence_matrix, bool* has_changed);
Incidence_Matrix* calculate_path_Incidence_Matrix(Incidence_Matrix* incidence_matrix);
ListHead* find_connected_groups(Incidence_Matrix* incidence_matrix, int* group_count);

bool is_node_in_array(Node* node, Node** array, int size);
void mark_secure_roads(Incidence_Matrix* incidence_matrix);

void create_road (Incidence_Matrix* mat, int A, int B);
void find_road_to_create(Incidence_Matrix* incidence_matrix);

#endif

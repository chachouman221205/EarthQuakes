#ifndef MATRIX
#define MATRIX

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Matrix {
    int size;
    Node** nodes;
    Road*** grid;
} Matrix;

#include "graph.h"
#include "linked_list.h"


Matrix* init_empty_matrix(int size);
Matrix* init_matrix_from_file(Variables* variables, char* fp);

void free_matrix_content(Matrix* matrix);
void free_matrix(Matrix* matrix);

int calculate_origin_path(Matrix* matrix, int node, int* distance);
void calculate_origin_distances(Matrix* matrix);
ListHead* find_path_to(Matrix* matrix, int node);
void print_path(Matrix* matrix, ListHead* path);

#endif

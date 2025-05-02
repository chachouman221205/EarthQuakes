#ifndef MATRIX
#define MATRIX

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"

typedef struct Matrix {
    int size;
    Node** nodes;
    Road*** grid;
} Matrix;

Matrix* init_empty_matrix(int size);
Matrix* init_matrix_from_file(Variables* variables, char* fp);

void free_matrix_content(Matrix* matrix);
void free_matrix(Matrix* matrix);

#endif

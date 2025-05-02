#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"

typedef struct Matrix {
    int size;
    Node** nodes;
    Road*** grid;
} Matrix;

Matrix* init_empty_matrix(int size) {
    Matrix* mat = malloc(1*sizeof(Matrix));
    mat->size = size;

    mat->nodes = malloc(size*sizeof(Node*));
    if (mat->grid == NULL) {
        printf(stderr, "Allocation ERROR in \"init_empty_matrix (1)\"\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        mat->nodes[i] = NULL;
    }

    mat->grid = malloc(size * sizeof(Road**));
    if (mat->grid == NULL) {
        printf(stderr, "Allocation ERROR in \"init_empty_matrix (2)\"\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        mat->grid[i] = malloc(size * sizeof(Road*));
        if (mat->grid[i] == NULL) {
            printf(stderr, "Allocation ERROR in \"init_empty_matrix (3)\"\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0 ; j < size; j++) {
            mat->grid[i][j] = NULL;
        }
    }

    return mat;
}

void free_matrix_content(Matrix* matrix) {
    for (int i = 0; i < matrix->size; i++) {
        for (int j = 0; j < matrix->size; j++) {
            if (matrix->grid[i][j] != NULL) {
                free_road(matrix->grid[i][j]);
            }
        }
    }

    for (int i = 0; i < matrix->size; i++) {
        free_node(matrix->nodes[i]);
    }
}

void free_matrix(Matrix* matrix) {
    for (int i = 0; i < matrix->size; i++) {
        free(matrix->grid[i]);
    }
    free(matrix->grid);
    free(matrix);
}

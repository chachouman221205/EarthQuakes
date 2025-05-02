#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"

Matrix* init_empty_matrix(int size) {
    Matrix* mat = malloc(1*sizeof(Matrix));
    mat->size = size;

    mat->nodes = malloc(size*sizeof(Node*));
    if (mat->grid == NULL) {
        fprintf(stderr, "\033[1;31mAllocation ERROR in \"init_empty_matrix (1)\"\033[0m\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        mat->nodes[i] = NULL;
    }

    mat->grid = malloc(size * sizeof(Road**));
    if (mat->grid == NULL) {
        fprintf(stderr, "\033[1;31mAllocation ERROR in \"init_empty_matrix (2)\"\033[0m\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        mat->grid[i] = malloc(size * sizeof(Road*));
        if (mat->grid[i] == NULL) {
            fprintf(stderr, "\033[1;31mAllocation ERROR in \"init_empty_matrix (3)\"\033[0m\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0 ; j < size; j++) {
            mat->grid[i][j] = NULL;
        }
    }

    return mat;
}

Matrix* init_matrix_from_file(char* fp) {
    /* Format de fichier :
     * ---------
     * size
     * A B poids
     * A C poids
     * ...
     * ...
     * Z Z poids
     * ---------
     *
     * ordre des connexions non important
     */

    FILE* f = fopen(fp, "r");
    int size;
    fscanf(f, "%d", &size);

    Matrix* mat = init_empty_matrix(size);

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

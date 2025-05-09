#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "graph.h"
#include "linked_list.h"

Matrix* init_empty_matrix(int size) {
    Matrix* mat = malloc(1*sizeof(Matrix));
    mat->size = size;

    mat->nodes = malloc(size*sizeof(Node*));
    if (mat->nodes == NULL) {
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

Matrix* init_matrix_from_file(Variables* variables, char* fp) {
    /* Format de fichier :
     * ---------
     * size
     * A B poids capacité
     * A C poids capacité
     * ...
     * ...
     * Z Y poids capacité
     * ---------
     *
     * ordre des connexions non important
     */

    FILE* f = fopen(fp, "r");
    int size;
    fscanf(f, "%d", &size);

    Matrix* mat = init_empty_matrix(size);
    for (int i = 0; i < size; i++) {
        mat->nodes[i] = init_node(variables, 'C');
    }

    int A, B, cap;
    unsigned int dist;
    srand(time(NULL));
    while (fscanf(f, "%d %d %u %d", &A, &B, &dist, &cap) != EOF) {
        mat->grid[A-1][B-1] = init_road(mat->nodes[A-1], mat->nodes[B-1], dist, rand()%5 != 0, cap);
    }

    fclose(f);
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

int calculate_origin_path(Matrix* matrix, int node) {
    unsigned int min_distance = -1;
    int min_node = -1;
    int temp;
    for (int i = 0; i < matrix->size; i++) {
        temp = matrix->grid[node][i]->distance + matrix->nodes[i]->distance_to_origin;
        if (temp < min_distance) {
            min_distance = temp;
            min_node = i;
        }
    }
    return min_node;
}
void calculate_origin_distances(Matrix* matrix) {
    ListHead* node_queue = ListInit();
    ListQueue(node_queue, 0);
    int current_node;
    // tant qu'il reste des noeuds à explorer
    while (node_queue->length > 0) {
        current_node = ListPop(node_queue, 0);

        int calculated_distance = calculate_origin_path(matrix, current_node);
        if (calculated_distance != matrix->nodes[current_node]->distance_to_origin) {
            matrix->nodes[current_node]->distance_to_origin = calculated_distance;

            // Marquer les voisins pour qu'ils soient recalculés
            for (int i = 0; i < matrix->size; i++) {
                if (matrix->grid[current_node][i] != NULL) {
                    ListQueue(node_queue, i);
                }
            }
        }

        // pour chaque voisin
        for (int i = 0; i < matrix->size; i++) {
            // qui existe et qui n'est pas exploré
            if (matrix->grid[current_node][i] != NULL && matrix->grid[current_node][i]->to->explored == false) {
                ListQueue(node_queue, i);
            }
        }
    }
    printf("\n");
    ListFree(node_queue);
    reset_exploration(matrix);
}

ListHead* find_path_to(Matrix* matrix, int node) {
    ListHead* path = ListInit();
    ListQueue(path, node);
    while (node != 0) {
        node = matrix->nodes[node]->towards_origin->to->ID;
        ListQueue(path, node);
    }
    return path;
}
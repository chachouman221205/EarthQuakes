#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "graph.h"
#include "linked_list.h"
#include "incidence_matrix.h"

bool is_node_in_array(Node* node, Node** array, int size){
    for(int i=0 ; i<size;i++){
        if(array[i] == node){
            return(true);
        }
    }
    return(false);
}

void Mission4(Matrix* matrix) {
    int tree_size = 0;
    Node** tree = NULL;
    tree = realloc(tree, (tree_size + 1) * sizeof(Node*));
    if (tree == NULL) {
        printf("Erreur d'alloc\n");
        exit(EXIT_FAILURE);
    }
    tree[tree_size] = matrix->nodes[0];
    tree_size++;

    while(tree_size < matrix->size){ // tant que tout les noeud ne sont pas connectés entres eux 
        tree = realloc(tree, (tree_size + 1) * sizeof(Node));
        if (tree == NULL) {
            printf("Erreur d'alloc\n");
        }

        int line=0;
        int column=0;
        for (int i = 0 ; i < tree_size ; i++){  //chercher la route connecté à tree_ la plus courte et la sécuriser 
            for (int y=0 ; y < tree[i]->connections_out ; y++ ){
                if(matrix->grid[i][y] != NULL){
                    if (matrix->grid[i][y]->distance < matrix->grid[line][column]->distance && is_node_in_array(matrix->nodes[column], tree, tree_size) == false){
                        line = i;
                        column = y;
                    }
                }
            }

        }


        tree[tree_size] = matrix->grid[line][column]->to;
        tree_size++;
        matrix->grid[line][column]->to_secure = true;       
    }

}

void Bonus1(Matrix* matrix){ // on part du principe qu'une route ajouté est de long=10 
    int road_to_create_number = matrix->size/10; // on s'autorise à créer 1/10 de route existante en plus ( à équilibrer )

    for (int i = road_to_create_number ; i > 0  ; i--){ // relier les noeud avec le plus de connection entrante aux noeuds avec le plus de connections sortante

    
    }
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
        printf("Road to secure from \033[0;36m%s%d\033[0m to \033[0;36m%s%d\033[0m :\n", 
            type1, road->from->ID, type2, road->to->ID);
    
         printf("\n");
    }
}

void print_roads_to_secure(Matrix* matrix){
    for(int line = 0; line < matrix->size; line++){
        for(int column = 0; column < matrix->size; column++){
            if(matrix->grid[line][column] != NULL){
                print_road_to_secure(matrix->grid[line][column]);
            }
        }
    }
}
int main() {
    Variables* var = init_variables();
    Matrix* mat = init_matrix_from_file(var, "test/gen_files/gen_graph10.txt");
    print_roads_to_secure(mat);
}
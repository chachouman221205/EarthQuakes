#include <stdlib.h>
#include <stdio.h>

#include "graph/graph.h"

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

void Mission1(int question, char* graph) {
    Variables* var = init_variables();
    Matrix* mat = init_matrix_from_file(var, graph);
    switch(question) {
        case 0:
            print_damage(mat);
            print_roads(mat);
            print_all_path_from_origin(mat);
            print_unaccessible_nodes(mat);
            break;
        case 1:
            print_roads(mat);
            break;
        case 2:
            print_all_path_from_origin(mat);
            break;
        case 3:
            print_unaccessible_nodes(mat);
            break;
        default :
            printf("ERROR\n");
            break;
    }
    free_matrix_content(mat);
    free_matrix(mat);
    free_variables_struct(var);
}

void Mission3(int question, char* graph) {
    Variables* var = init_variables();
    Matrix* mat = init_matrix_from_file(var, graph);

    switch (question) {
        case 1:
            int node;
            printf("Which node do you want to access ?\nEnter a number (1-%d) : ", mat->size);
            scanf("%d", &node);
            ListHead* path = find_path_to(mat, node-1);
            if (path == NULL) {
                printf("\033[1;31mThere are no existing path to %c%d\033[0m\n",
                    mat->nodes[node-1]->type, mat->nodes[node-1]->ID);
            } else {
                printf("Path to %c%d : ", 
                    mat->nodes[node-1]->type, mat->nodes[node-1]->ID);
                int length;
                print_path(mat, path, &length);
                printf("\n\033[1m ⤷\033[0m Total length : %d\n", length);
                ListFree(path);
            }
            break;
        case 2:
            printf("\n");
            break;
        default :
            printf("ERROR\n");
            break;
    }
    free_matrix_content(mat);
    free_matrix(mat);
    free_variables_struct(var);
}

int main(){
    printf(" \b\n\n\n");

    char filename[50];
    *filename = *find_file(filename);
    Mission1(0, filename);

    Mission3(1, filename);

    return 0;
}

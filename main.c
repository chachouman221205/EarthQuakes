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

void Mission2(char* graph) {
    Variables* var = init_variables();
    Matrix* mat = init_matrix_from_file(var, graph);

    int n;
    int _;
    ListHead* groups = find_connected_groups(mat, &n);
    printf("The groups of nodes where you can freely move are :\n");
    for (int i = 0; i < n; i++) {
        printf("  ⤷ Group %2d : ", i);
        print_path(mat, &groups[i], &_);
        printf("\n");
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
            printf("Which node do you want to access ?\nEnter a number (1-%d) (C0 = 1 etc) : ", mat->size);
            scanf("%d", &node);
            if((int)node < 1 || (int)node > mat->size){
                printf("\033[0;31mERROR : Invalid node number\033[0m\n");
                while(getchar() != '\n');
                return Mission3(question, graph);
            }
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

void Mission4(char* graph) {
    Variables* var = init_variables();
    Matrix* mat = init_matrix_from_file(var, graph);

    mark_secure_roads(mat);
    print_roads_to_secure(mat);

    free_matrix_content(mat);
    free_matrix(mat);
    free_variables_struct(var);
}

void Bonus1(char* graph) {
    Variables* var = init_variables();
    Matrix* mat = init_matrix_from_file(var, graph);

    find_road_to_create(mat);
    print_roads_created(mat);

    free_matrix_content(mat);
    free_matrix(mat);
    free_variables_struct(var);
}

int main(){
    printf(" \b\n\n");

    char filename[50];
    *filename = *find_file(filename);
    Mission1(0, filename);
    Mission2(filename);
    Mission3(1, filename);
    Mission4(filename);
    //Bonus1(filename);


    return 0;
}

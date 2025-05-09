#include <stdlib.h>
#include <stdio.h>

#include "graph/graph.h"

char* find_file(char* filename){
    FILE *f;
    int name_id = 1;

    // Trouver un nom de fichier qui n'existe pas encore
    do {
        sprintf(filename, "gen_graph%d.txt", name_id);
        f = fopen(filename, "r");
        if(f != NULL) {
            fclose(f);
            name_id++;
        }
    } while(f != NULL);

    sprintf(filename, "gen_graph%d.txt", --name_id);
    printf("%s\n", filename);
    return filename;
}

void Mission1(int question, char* graph) {
    Variables* var = init_variables();
    Matrix* mat = init_matrix_from_file(var, graph);
    switch(question) {
        case 0:
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
    }
    free_matrix_content(mat);
    free_matrix(mat);
}

int main(){
    printf(" \b\n\n\n");

    char filename[50];
    Mission1(0, find_file(filename));

    return 0;
}

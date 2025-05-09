#include <stdlib.h>
#include <stdio.h>

#include "graph/graph.h"

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

    Mission1(0, "gen_graph.txt");

    return 0;
}

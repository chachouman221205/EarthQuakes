#include <stdlib.h>
#include <stdio.h>

#include "graph/graph.h"

void Mission1(int question, char* graph) {
    Variables* var = init_variables();
    Matrix* mat = init_matrix_from_file(var, graph);
    switch(question) {
        case 1:
            print_roads(mat);
            break;
        case 2:
            printf("The accessible nodes are :\n  -> ");
            print_all_path_from_origin(mat);
            break;
    }
    free_matrix_content(mat);
    free_matrix(mat);
}

int main(){
    printf(" \b");

    Mission1(2, "test/graph1.txt");

    return 0;
}

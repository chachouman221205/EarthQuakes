#include <stdlib.h>
#include <stdio.h>

#include "graph/graph.h"

void Mission1(int question, char* graph) {
    switch(question) {
        case 1:
            Variables* var = init_variables();
            Matrix* mat = init_matrix_from_file(var, graph);

            print_roads(mat);

            free_matrix_content(mat);
            free_matrix(mat);
    }
}

int main(){
    printf(" \b");

    Mission1(1, "test/graph1.txt");

    return 0;
}

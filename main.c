#include <stdlib.h>
#include <stdio.h>

#include "graph/graph.h"

int main(){
    printf(" \b");

    Matrix* mat = init_matrix_from_file("test/graph1.txt");

    free_matrix_content(mat);
    free_matrix(mat);

    return 0;
}

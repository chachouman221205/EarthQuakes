#include <stdlib.h>
#include <stdio.h>

#include "graph/graph.h"
#include "graphic_interface/interface.h"



int main(){
    printf(" \b\n\n");

    char filename[50];
    *filename = *find_file(filename);

    // Mission1(0, filename);
    // Mission2(filename);
    // Mission3(1, filename);
    // Mission4(filename);
    // Bonus1(filename);

    app_start(filename);


    return 0;
}

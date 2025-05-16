#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "graph/graph.h"
#include "graphic_interface/interface.h"



int main(){
    printf(" \b\n\n");

    char filename[50];
    *filename = *find_file(filename);

    Variables* var = init_variables();
    Incidence_Matrix* mat = init_incidence_matrix_from_file(var, filename);

    Mission1(0, var, mat);
    sleep(1);
    Mission2(var, mat);
    sleep(1);
    Mission3(1, var, mat);
    sleep(1);
    Mission4(var, mat);
    sleep(1);
    Bonus1(var, mat);
    sleep(1);

    // app_start(filename);

    printf("\033[1;31m \n/!\\ TRIGGERING AN EARTHQUAKE /!\\ \033[0m\n\n");
    Earthquake(mat);

    int mission = 1;
    printf("Which Mission do you want to try ?\n (1 = Mission1, 6 = Bonus1, 0 = exit program)\n");
    while (mission != 0) {
        scanf("%d", &mission);
        switch (mission) {
            case 0:
                printf("Exiting program\n");
                break;
            case 1:
                Mission1(0, var, mat);
                printf("Which Mission do you want to try ?\n (1 = Mission1, 6 = Bonus1, 0 = exit program)\n");
                break;
            case 2:
                Mission2(var, mat);
                printf("Which Mission do you want to try ?\n (1 = Mission1, 6 = Bonus1, 0 = exit program)\n");
                break;
            case 3:
                Mission3(1, var, mat);
                printf("Which Mission do you want to try ?\n (1 = Mission1, 6 = Bonus1, 0 = exit program)\n");
                break;
            case 4:
                Mission4(var, mat);
                printf("Which Mission do you want to try ?\n (1 = Mission1, 6 = Bonus1, 0 = exit program)\n");
                break;
            case 5:
                printf("Mission 5 is not available\n");
                break;
            case 6:
                Bonus1(var, mat);
                printf("Which Mission do you want to try ?\n (1 = Mission1, 6 = Bonus1, 0 = exit program)\n");
                break;
            case 7:
                printf("Bonus 2 is not available\n");
                printf("Which Mission do you want to try ?\n (1 = Mission1, 6 = Bonus1, 0 = exit program)\n");
                break;
            default:
                printf("Mission number is not recognized, please enter a new number");
        }
    }


    free_incidence_matrix_content(mat);
    free_incidence_matrix(mat);
    free_variables_struct(var);

    return 0;
}

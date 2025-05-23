#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "../../graph/graph.h"

int main(){
    /* Format de fichier :
    * ---------
    * size
    * A B poids capacité
    * A C poids capacité
    * ...
    * ...
    * Z Y poids capacité
    * ---------
    *
    * ordre des connexions non important
    */
   
   FILE *f;
   char filename[50];
   int file_id = 1;
   
   // Trouver un nom de fichier qui n'existe pas encore
   do {
       sprintf(filename, "gen_graph%d.txt", file_id);
        f = fopen(filename, "r");
        if(f != NULL) {
            fclose(f);
            file_id++;
        }
    } while(f != NULL);

    // Ouvrir le fichier pour écriture
    f = fopen(filename, "w");
    if(f == NULL) {printf("\033[0;31mERROR oppening file\033[0m\n"); return 1;}

    srand(time(NULL));

    int max_size = 15, min_size = 5, link_chance = (max_size-1) / 3;
    int rand_size = (rand() % max_size);
    if(rand_size < min_size) rand_size = min_size;
    
    rand_size = 10;
    
    printf("\n\033[1;35mMATRIX SIZE :\033[0m %d", rand_size);

    fprintf(f, "%d\n", rand_size);
    
    int max_dist = 10, max_capa = 10;

    int min_lines = 1, lines = 0;
    for(int i = 0; i < rand_size; i++){
        for(int ii = 0; ii < rand_size; ii++){
            if(i != ii && ((rand()%link_chance) == 0 || lines < min_lines)){
                fprintf(f, "%d %d %d %d\n", i+1, ii+1, rand()%max_dist+1, rand()%max_capa+1);
                lines++;
                // printf("%c - %c | ", nodes[i], nodes[ii]);
            }
        }// printf("\n");
        lines = 0;
    }
    
    fclose(f);

    //----------- CORRECTION LINES -----------//

    Variables* var = init_variables();
    Incidence_Matrix* mat = init_incidence_matrix_from_file(var, filename);

    f = fopen(filename, "a");
    if(f == NULL) {
        printf("\033[0;31mERROR oppening file\033[0m\n"); 
        
        free_incidence_matrix_content(mat);
        free_incidence_matrix(mat);
        free_variables_struct(var);
        return 1;
    }
    // fprintf(f, "1 1 1 1\n");

    explore_all_nodes_width(mat);
    for(int i = 0; i < mat->size; i++){
        if(mat->nodes[i]->explored == false){
            int a = rand()%rand_size;
            while(a == i || mat->nodes[a]->explored == false) a = rand()%rand_size;
            // printf("\033[1;35mFILE : \033[0madded line \"%d %d %d %d\"\n", 
                // a+1, i+1, rand()%max_dist+1, rand()%max_capa+1);
            printf("\033[1;35mFILE : \033[0madded road : C%d → C%d\n", a, i);
            fprintf(f, "%d %d %d %d\n", a+1, i+1, rand()%max_dist+1, rand()%max_capa+1);
            
            reset_exploration(mat);
            explore_all_nodes_width(mat);
        }
    }

    fclose(f);

    free_incidence_matrix_content(mat);
    free_incidence_matrix(mat);
    free_variables_struct(var);
    return 0;
}

//cd test/gen_files && gcc -o file_gen.exe file_gen.c && cd .. && cd ..

// ls && echo && cd test && ls && echo && cd gen_files && ls && cd .. && cd ..

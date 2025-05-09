#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

    // le numéro du graphe à créé
    FILE* f = fopen("test.conf", "r");
    int file_number; fscanf(f, "%d", &file_number);
    fclose(f);

    srand(time(NULL));
    f = fopen("gen_file.txt", "w");
    if(f == NULL){ printf("Error opening file!\n"); return 1;}

    int max_size = 10, min_size = 3, link_chance = (max_size-1) / 3;
    int rand_size = (rand() % max_size);
    if(rand_size < min_size) rand_size = min_size;
    fprintf(f, "%d\n", rand_size);
    
    char nodes[rand_size+1];
    for(int i = 0; i < rand_size; i++){
        nodes[i] = i+1; // nodes[i] = 'A' + i; // printf("%c ", nodes[i]);
    }// printf("\n");
    
    int max_dist = 10, max_capa = 10;

    int rand_i = rand() % max_size+1;
    for(int i = 0; i < rand_size; i++){
        for(int ii = 0; ii < rand_size -1; ii++){
            if(i != ii && (rand()%link_chance) == 0){
                fprintf(f, "%d %d %d %d\n", nodes[i], nodes[ii], rand()%max_dist+1, rand()%max_capa+1);
                // printf("%c - %c | ", nodes[i], nodes[ii]);
            }
        }// printf("\n");
    }

    fclose(f);
    return 0;
}

//cd test && gcc -o file_gen.exe file_gen.c && cd ..
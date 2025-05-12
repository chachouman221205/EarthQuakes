#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "graph.h"
#include "linked_list.h"
#include "incidence_matrix.h"

bool XAlready_use(Node X , Node liste , int size){
    for(int i=0 ; i<size;i++){
        if(liste[i] == X){
            return(true);
        }
    }
    return(false);
}


void Mission4(Matrix* matrix) {
    int Xsize = 0; // ici X symbolise l'arbre connex le plus court du graphe ( que l'on cherche )
    Node *Xconnected = NULL;
    realloc(Xconnected, (Xsize + 1) * sizeof(Node));
    if (temp == NULL) {
        printf("Erreur d'alloc\n");
    }
    Xconnected = temp;
    Xconnected[Xsize] = matrix->nodes[0];
    Xsize++;

    while(Xsize < matrix->size){ // tant que tout les noeud ne sont pas connectés entres eux 
        realloc(Xconnected, (Xsize + 1) * sizeof(Node));
        if (Xconnected == NULL) {
            printf("Erreur d'alloc\n");
        }

        int line=NULL;
        int column=NULL;
        for (int i = 0 ; i < Xsize ; i++){  //chercher la route connecté à X la plus courte et la sécuriser 
            for (int y=0 ; y < Xconnected[i]->connections_out ; y++ ){
                if(matrix->grid[i][y] != NULL){
                    if (matrix->grid[i][y]->distance < matrix->grid[line][colum] && XAlready_use(matrix->grid[line][column]->to,*Xconnected, Xsize) == false){
                        line = i;
                        column = y;
                    }
                }
            }

        }   
        Xconnected[Xsize] = matrix->grid[line][column]->to;
        Xsize++;
        matrix->grid[line][column]->to_secure = true;       
    }

}

Void Bonus1(Matrix* matrix){ // on part du principe qu'une route ajouté est de long=10 
    int road_to_create_number = matrix->size/10; // on s'autorise à créer 1/10 de route existante en plus ( à équilibrer )

    for int (i = road_to_create_number ; i > 0  ; i--){ // relier les noeud avec le plus de connection entrante aux noeuds avec le plus de connections sortante

    
    }
}







void print_road_to_secure(Road* road){
    char type1[20], type2[20];
    switch (road->from->type) {
        case 'C':
            strcpy(type1, "City");
            break;
        case 'H':
            strcpy(type1, "Hospital");
            break;
        case 'W':
            strcpy(type1, "Warehouse");
            break;
        default:
            strcpy(type1, "Unknown");
    }
    switch (road->to->type) {
        case 'C':
            strcpy(type2, "City");
            break;
        case 'H':
            strcpy(type2, "Hospital");
            break;
        case 'W':
            strcpy(type2, "Warehouse");
            break;
        default:
            strcpy(type2, "Unknown");
    }
    if road->to_secure == true {
        printf("Road to secure from \033[0;36m%s%d\033[0m to \033[0;36m%s%d\033[0m :\n", 
            type1, road->from->ID, type2, road->to->ID);
    
         printf("\n");
    }
}

void print_roads_to_secure(Matrix* matrix){
    for(int line = 0; line < matrix->size; line++){
        for(int column = 0; column < matrix->size; column++){
            if(matrix->grid[line][column] != NULL){
                print_road_to_secure(matrix->grid[line][column]);
            }
        }
    }
}
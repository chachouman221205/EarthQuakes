#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "graph.h"
#include "linked_list.h"


void Mission4(Matrix* matrix) {
    bool all_connected = false;
    while(all_connected == false){ // tant que tout les noeud ne sont pas connectés entres eux 

        
            //chercher les node avec le plus de connections et sécuiser la route la plus courte qui vas sur le node avec le plus de connections




        for(int i = 0 ; i < matrix->size ; i++){ // vérifie si tout les "node" sont connecté entre eux , si oui -> all connnected = true -> on sort du while
            if (matrix->nodes[i]->explored == false){
                all_connected == false;
                break;
            }
            else{
                if (i == matrix->size-1 && matrix->nodes[i]->explored == true){
                    all_connected == true;
                }  
            }
        }
    }



    reset_exploration(matrix)
}

Void Bonus1(Matrix* matrix){ // on part du principe qu'une route ajouté est de long=10 
    int road_to_create_number = matrix->size/10; // on s'autorise à créer 1/10 de route existante en plus ( à équilibrer )

    for int (i = road_to_create_number ; i > 0  ; i--){

        
    }
}
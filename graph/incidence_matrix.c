#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "graph.h"
#include "linked_list.h"
#include "incidence_matrix.h"

Incidence_Matrix* init_empty_incidence_matrix(int size) {
    Incidence_Matrix* mat = malloc(1*sizeof(Incidence_Matrix));
    mat->size = size;

    mat->nodes = malloc(size*sizeof(Node*));
    if (mat->nodes == NULL) {
        fprintf(stderr, "\033[1;31mAllocation ERROR in \"init_empty_incidence_matrix (1)\"\033[0m\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        mat->nodes[i] = NULL;
    }

    mat->grid = malloc(size * sizeof(Road**));
    if (mat->grid == NULL) {
        fprintf(stderr, "\033[1;31mAllocation ERROR in \"init_empty_incidence_matrix (2)\"\033[0m\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        mat->grid[i] = malloc(size * sizeof(Road*));
        if (mat->grid[i] == NULL) {
            fprintf(stderr, "\033[1;31mAllocation ERROR in \"init_empty_incidence_matrix (3)\"\033[0m\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0 ; j < size; j++) {
            mat->grid[i][j] = NULL;
        }
    }

    return mat;
}

Incidence_Matrix* init_incidence_matrix_from_file(Variables* variables, char* fp) {
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

    FILE* f = fopen(fp, "r");
    if(f == NULL){
        printf("\033[31mERROR\033[0m: oppening file in init_incidence_matrix_from_file : %s\n", fp);
        exit(1);
    }
    int size;
    fscanf(f, "%d", &size);

    Incidence_Matrix* mat = init_empty_incidence_matrix(size);
    for (int i = 0; i < size; i++) {
        mat->nodes[i] = init_node(variables, 'C');
    }

    int A, B, cap;
    unsigned int dist;
    srand(time(NULL));
    while (fscanf(f, "%d %d %u %d", &A, &B, &dist, &cap) != EOF) {
        if (mat->grid[A-1][B-1] != NULL) {
            printf("\033[0;31mError while reading file:\033[0m Double road declaration (%d -> %d)\n", A, B);
            exit(EXIT_FAILURE);
        }
        mat->grid[A-1][B-1] = init_road(mat->nodes[A-1], mat->nodes[B-1], dist, true, cap); // rand()%5 != 0
    }

    fclose(f);

    // préparation de la matrice pour les calculs
    calculate_origin_distances(mat);

    return mat;
}

Incidence_Matrix* copy_incidence_matrix_content(Incidence_Matrix* source) {
    Incidence_Matrix* dest = init_empty_incidence_matrix(source->size);
    for (int i = 0; i < source->size; i++) {
        dest->nodes[i] = source->nodes[i];
        for (int j = 0; j < source->size; j++) {
            dest->grid[i][j] = source->grid[i][j];
        }
    }
    return dest;
}

void free_incidence_matrix_content(Incidence_Matrix* incidence_matrix) {
    for (int i = 0; i < incidence_matrix->size; i++) {
        for (int j = 0; j < incidence_matrix->size; j++) {
            if (incidence_matrix->grid[i][j] != NULL) {
                free_road(incidence_matrix->grid[i][j]);
            }
        }
    }

    for (int i = 0; i < incidence_matrix->size; i++) {
        free_node(incidence_matrix->nodes[i]);
    }
}

void free_incidence_matrix(Incidence_Matrix* incidence_matrix) {
    for (int i = 0; i < incidence_matrix->size; i++) {
        free(incidence_matrix->grid[i]);
    }
    free(incidence_matrix->grid);
    free(incidence_matrix->nodes);
    free(incidence_matrix);
}


int calculate_origin_path(Incidence_Matrix* incidence_matrix, int node, int* distance) {
    if (node == 0) {
        *distance = 0;
        return -1;
    }
    unsigned int min_distance = -1;
    int min_node = -1;
    int temp;
    for (int i = 0; i < incidence_matrix->size; i++) {
        if (incidence_matrix->grid[i][node] == NULL || incidence_matrix->nodes[i]->distance_to_origin == -1) {
            continue;
        }

        temp = incidence_matrix->grid[i][node]->distance + incidence_matrix->nodes[i]->distance_to_origin;
        if (temp < min_distance) {
            min_distance = temp;
            min_node = i;
        }
    }
    *distance = min_distance;
    return min_node;
}
void calculate_origin_distances(Incidence_Matrix* incidence_matrix) {
    ListHead* node_queue = ListInit();
    ListQueue(node_queue, 0);
    int current_node = 0;
    incidence_matrix->nodes[0]->distance_to_origin = 0;
    incidence_matrix->nodes[0]->towards_origin = NULL;
    // tant qu'il reste des noeuds à explorer
    while (node_queue->length > 0) {
        current_node = ListPop(node_queue, 0);

        // pour chaque voisin
        for (int i = 0; i < incidence_matrix->size; i++) {
            // qui existe et qui n'est pas exploré
            if (incidence_matrix->grid[current_node][i] != NULL && incidence_matrix->nodes[i]->explored == false) {
                ListQueue(node_queue, i);
                incidence_matrix->nodes[i]->explored = true;
            }
        }

        int calculated_distance;
        int node_towards_origin = calculate_origin_path(incidence_matrix, current_node, &calculated_distance);
        if (node_towards_origin == -1) { // Aucun chemin ne peut être calculé
            continue;
        }
        // Si aucun chemin n'a été calculé, ou si la distance n'est pas la même, ou si le prochain noeud n'est pas le même
        if (incidence_matrix->nodes[current_node]->towards_origin == NULL
            || calculated_distance != incidence_matrix->nodes[current_node]->distance_to_origin
            || node_towards_origin != incidence_matrix->nodes[current_node]->towards_origin->from->ID
        ) {
            incidence_matrix->nodes[current_node]->distance_to_origin = calculated_distance;
            incidence_matrix->nodes[current_node]->towards_origin = incidence_matrix->grid[node_towards_origin][current_node];

            // Marquer les voisins pour qu'ils soient recalculés
            for (int i = 0; i < incidence_matrix->size; i++) {
                if (incidence_matrix->grid[current_node][i] != NULL && !ListContains(node_queue, i)) {
                    ListQueue(node_queue, i);
                }
            }
        }

        
    }
    printf("\n");
    ListFree(node_queue);
    reset_exploration(incidence_matrix);
}

ListHead* find_path_to(Incidence_Matrix* incidence_matrix, int node) {
    ListHead* path = ListInit();
    ListQueue(path, node);
    while (node != 0) {
        if (incidence_matrix->nodes[node]->towards_origin == NULL) {
            ListFree(path);
            return NULL;
        }
        node = incidence_matrix->nodes[node]->towards_origin->from->ID;
        ListQueue(path, node);
    }
    ListReverse(path);
    return path;
}

void print_path(Incidence_Matrix* incidence_matrix, ListHead* path, int* length) {
    ListNode* ptr = path->next;
    while (ptr != NULL) {
        Node* node = incidence_matrix->nodes[ptr->data];
        printf("%c%d ", node->type, node->ID);
        *length = node->distance_to_origin;
        ptr = ptr->next;
    }
}

void multiply_incidence_matrix(Incidence_Matrix* incidence_matrix, bool* has_changed) {
    /*
    S'il existe un chemin de i vers k, et de k vers j,
    alors on affecte à i->j le chemin i->k

    Si aucun changement n'a été fait, alors has_changed sera mis à false.
    Cela permet d'éviter d'appeler cette fonction de complexité O(n3) inutilement
    */
    *has_changed = false;
    for (int i = 0; i < incidence_matrix->size; i++) {
        for (int j = 0; j < incidence_matrix->size; j++) {
            if (incidence_matrix->grid[i][j] == NULL) {
                for (int k = 0; k < incidence_matrix->size; k++) {
                    if (is_usable(incidence_matrix->grid[i][k]) && is_usable(incidence_matrix->grid[k][j])) {
                        incidence_matrix->grid[i][j] = incidence_matrix->grid[i][k];
                        *has_changed = true;
                        break;
                    }
                }
            }
        }
    }
}

Incidence_Matrix* calculate_path_incidence_matrix(Incidence_Matrix* incidence_matrix) {
    incidence_matrix = copy_incidence_matrix_content(incidence_matrix); // Copier pour pouvoir appliquer des opérations sans affecter la matrice de départ
    bool has_changed = true;
    for (int i = 0; i < incidence_matrix->size && has_changed; i++) {
        multiply_incidence_matrix(incidence_matrix, &has_changed);
    }
    return incidence_matrix;
}

ListHead* find_connected_groups(Incidence_Matrix* incidence_matrix, int* group_count) {
    incidence_matrix = calculate_path_incidence_matrix(incidence_matrix);

    int* _nodes = malloc(incidence_matrix->size * sizeof(int));
    for (int i = 0; i < incidence_matrix->size; i++) {
        _nodes[i] = i;
    }
    ListHead* nodes = ListFromArray(_nodes, incidence_matrix->size); // Liste des noeuds toujours disponibles

    ListHead* groups = NULL;
    ListHead* current_group;
    int current_group_base;
    *group_count = 0;
    while (nodes->length > 0) {
        // Ajout d'un nouveau groupe de sommets
        (*group_count)++;
        groups = realloc(groups, (*group_count) * sizeof(ListHead));
        
        current_group = &groups[*group_count - 1];
        current_group->length = 0;
        current_group->next = NULL;
        current_group_base = ListPop(nodes, 0);
        ListQueue(current_group, current_group_base);

        ListNode* _;
        for (ListNode* i = nodes->next; i != NULL;) {
            // Si un chemin existe dans les deux sens
            if (is_usable(incidence_matrix->grid[current_group_base][i->data]) && is_usable(incidence_matrix->grid[i->data][current_group_base])) {
                // On ajoute le sommet au groupe actuel, et on le retire de la liste commune
                ListQueue(current_group, i->data);
                _ = i->next;
                ListRemove(nodes, i->data);
                i = _;
            } else {
                i = i->next;
            }
        }
    }
    return groups;
}

bool is_node_in_array(Node* node, Node** array, int size){
    for(int i=0 ; i<size;i++){
        if(array[i] == node){
            return(true);
        }
    }
    return(false);
}

void mark_secure_roads(Incidence_Matrix* incidence_matrix) {
    int tree_size = 0;
    Node** tree = NULL;
    tree = realloc(tree, (tree_size + 1) * sizeof(Node*));
    if (tree == NULL) {
        printf("Erreur d'alloc\n");
        exit(EXIT_FAILURE);
    }
    tree[tree_size] = incidence_matrix->nodes[0];
    tree_size++;

    while(tree_size < incidence_matrix->size){ // tant que tout les noeud ne sont pas connectés entres eux 
        int i_min=0;
        int j_min=0;
        for (int i = 0; i < incidence_matrix->size; i++){  //chercher la route connecté à tree_ la plus courte et la sécuriser
            if (!is_node_in_array(incidence_matrix->nodes[i], tree, tree_size)) {
                continue;
            }

            for (int j = 0; j < incidence_matrix->size; j++ ){
                if(incidence_matrix->grid[i][j] != NULL){
                    if (incidence_matrix->grid[i][j]->to_secure) {
                        continue;
                    }
                    if (incidence_matrix->grid[i_min][j_min] == NULL) {
                        i_min = i;
                        j_min = j;
                        continue;
                    }
                    if (incidence_matrix->grid[i][j]->distance < incidence_matrix->grid[i_min][j_min]->distance && !is_node_in_array(incidence_matrix->nodes[j], tree, tree_size)){
                        i_min = i;
                        j_min = j;
                    }
                }
            }

        }

        tree_size++;
        tree = realloc(tree, (tree_size) * sizeof(Node));
        if (tree == NULL) {
            printf("Erreur d'alloc\n");
        }
        tree[tree_size-1] = incidence_matrix->nodes[j_min];
        incidence_matrix->grid[i_min][j_min]->to_secure = true;
    }

    free(tree);
}

void create_road (Incidence_Matrix* mat, int A, int B){
    mat->grid[A][B] = init_road(mat->nodes[A], mat->nodes[B], 10 , true, 6); // ici distance mise à 10 et capacity à 6 ( à modifier )
    mat->grid[A][B]->is_created = true;
}

void find_road_to_create(Incidence_Matrix* incidence_matrix){ //Bonus 1
    int created_road = 0 ;
    int number_road_to_create = incidence_matrix->size/10; // on set le nombre de route à créer à 1 dixième de la taille du graphe
    printf("There are %d roads to create\n", number_road_to_create - created_road);
    while(created_road < number_road_to_create){ // on répete l'action de créer une route jusqu'a que les 10 routes soit crées 
        int i_min=0;
        int i_max=0;
        int delta = incidence_matrix->nodes[0]->connections_in - incidence_matrix->nodes[0]->connections_out;
        int delta_min = delta;
        int delta_max = delta;

        for (int i = 0; i < incidence_matrix->size; i++){
            if (incidence_matrix->nodes[i]->explored) continue;

            delta = incidence_matrix->nodes[i]->connections_in - incidence_matrix->nodes[i]->connections_out;
            if (delta > delta_max){
                i_max = i;
                delta_max = delta;
            } // cherche le sommet avec le deltaSortie le plus élevé
            if (delta < delta_min){
                i_min = i;
                delta_min = delta;
            }  // cherche le sommet avec le deltaEntrée le plus élevé
        }

        if(incidence_matrix->grid[i_max][i_min] == NULL && i_min != i_max){ // si la route entre les 2 sommets n'existe pas encore et que i_min est différent de j_min alors on crée la route
            create_road(incidence_matrix, i_max, i_min);
            created_road++;
            printf("  ⤷ Road %d created\n" ,created_road);
            reset_exploration(incidence_matrix);
        }
        else { // sinon on marque le sommet entré pour dire qu'il n'est pas utilisable pour l'instant
            incidence_matrix->nodes[i_max]->explored = true;
            incidence_matrix->nodes[i_min]->explored = true;
        }
    }
    reset_exploration(incidence_matrix);
}

void truck_travel() {

}

bool citys_is_repared(Incidence_Matrix* incidence_matrix){
    for(int i=0 ; i < incidence_matrix->size ; i++){
        if (incidence_matrix->nodes[i]->Is_repared == false ){
            return false;
        }
    }
    return true;

}

void verif_city_reparation(Incidence_Matrix* incidence_matrix){
    for (int i = 0 ; i < incidence_matrix->size ; i++){
        if( incidence_matrix->nodes[i]->current_capacity[4] == 100 ){
            incidence_matrix->nodes[i]->Is_repared = true;
        }
    }
}

void repare_city(Incidence_Matrix* incidence_matrix){
    int time = 0;
    int timeBeforeTruck = 0;
    while ( citys_is_repared(incidence_matrix) != true){ // tant que toute les villes ne sont pas réparés

        // il fautenvoyer des  camions pour aprovisioner les villes en matériaux 
        // on verifie si on a des camion libre 
        // si oui on l'envoie ravitailler X ville dans le besoin 
        // On trace son trajet 
        // une fois le camion vide --> retour à la case départ ( ou à l'entrepot le plus proche dans l'idéal )
        // retour à l'étape 1

        // augementer le temps de 1 à chauqe "tick"

        if (timeBeforeTruck <= 0){  // manière frauduleuse deréparer les villes (code temporaire)
            for (int i = 0 ; i < incidence_matrix->size; i++){
                if  (incidence_matrix->nodes[i]->Is_repared == false){
                    incidence_matrix->nodes[i]->current_capacity[4] = 100;
                    timeBeforeTruck = 2* incidence_matrix->nodes[i]->distance_to_origin + 1;
                    i= incidence_matrix->size ;
                }
            }

        }

        verif_city_reparation(incidence_matrix); // actualise l'état des villes 
        timeBeforeTruck--;
        time++;
    }
    printf("\nIt took %d ticks to repair all roads\n" , time);

}

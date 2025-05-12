#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "graph.h"
#include "linked_list.h"
#include "incidence_matrix.h"

Matrix* init_empty_matrix(int size) {
    Matrix* mat = malloc(1*sizeof(Matrix));
    mat->size = size;

    mat->nodes = malloc(size*sizeof(Node*));
    if (mat->nodes == NULL) {
        fprintf(stderr, "\033[1;31mAllocation ERROR in \"init_empty_matrix (1)\"\033[0m\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        mat->nodes[i] = NULL;
    }

    mat->grid = malloc(size * sizeof(Road**));
    if (mat->grid == NULL) {
        fprintf(stderr, "\033[1;31mAllocation ERROR in \"init_empty_matrix (2)\"\033[0m\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        mat->grid[i] = malloc(size * sizeof(Road*));
        if (mat->grid[i] == NULL) {
            fprintf(stderr, "\033[1;31mAllocation ERROR in \"init_empty_matrix (3)\"\033[0m\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0 ; j < size; j++) {
            mat->grid[i][j] = NULL;
        }
    }

    return mat;
}

Matrix* init_matrix_from_file(Variables* variables, char* fp) {
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
        printf("\033[31mERROR\033[0m: oppening file in init_matrix_from_file : %s\n", fp);
        exit(1);
    }
    int size;
    fscanf(f, "%d", &size);

    Matrix* mat = init_empty_matrix(size);
    for (int i = 0; i < size; i++) {
        mat->nodes[i] = init_node(variables, 'C');
    }

    int A, B, cap;
    unsigned int dist;
    srand(time(NULL));
    while (fscanf(f, "%d %d %u %d", &A, &B, &dist, &cap) != EOF) {
        if (mat->grid[A-1][B-1] != NULL) {
            printf("\033[31mError while reading file:\033[0m Double road declaration (%d -> %d)\n", A, B);
            exit(EXIT_FAILURE);
        }
        mat->grid[A-1][B-1] = init_road(mat->nodes[A-1], mat->nodes[B-1], dist, true, cap); // rand()%5 != 0
    }

    fclose(f);

    // préparation de la matrice pour les calculs
    calculate_origin_distances(mat);

    return mat;
}

Matrix* copy_matrix_content(Matrix* source) {
    Matrix* dest = init_empty_matrix(source->size);
    for (int i = 0; i < source->size; i++) {
        dest->nodes[i] = source->nodes[i];
        for (int j = 0; j < source->size; j++) {
            dest->grid[i][j] = source->grid[i][j];
        }
    }
    return dest;
}

void free_matrix_content(Matrix* matrix) {
    for (int i = 0; i < matrix->size; i++) {
        for (int j = 0; j < matrix->size; j++) {
            if (matrix->grid[i][j] != NULL) {
                free_road(matrix->grid[i][j]);
            }
        }
    }

    for (int i = 0; i < matrix->size; i++) {
        free_node(matrix->nodes[i]);
    }
}

void free_matrix(Matrix* matrix) {
    for (int i = 0; i < matrix->size; i++) {
        free(matrix->grid[i]);
    }
    free(matrix->grid);
    free(matrix->nodes);
    free(matrix);
}


int calculate_origin_path(Matrix* matrix, int node, int* distance) {
    if (node == 0) {
        *distance = 0;
        return -1;
    }
    unsigned int min_distance = -1;
    int min_node = -1;
    int temp;
    for (int i = 0; i < matrix->size; i++) {
        if (matrix->grid[i][node] == NULL || matrix->nodes[i]->distance_to_origin == -1) {
            continue;
        }

        temp = matrix->grid[i][node]->distance + matrix->nodes[i]->distance_to_origin;
        if (temp < min_distance) {
            min_distance = temp;
            min_node = i;
        }
    }
    *distance = min_distance;
    return min_node;
}
void calculate_origin_distances(Matrix* matrix) {
    ListHead* node_queue = ListInit();
    ListQueue(node_queue, 0);
    int current_node = 0;
    matrix->nodes[0]->distance_to_origin = 0;
    matrix->nodes[0]->towards_origin = NULL;
    // tant qu'il reste des noeuds à explorer
    while (node_queue->length > 0) {
        current_node = ListPop(node_queue, 0);

        // pour chaque voisin
        for (int i = 0; i < matrix->size; i++) {
            // qui existe et qui n'est pas exploré
            if (matrix->grid[current_node][i] != NULL && matrix->nodes[i]->explored == false) {
                ListQueue(node_queue, i);
                matrix->nodes[i]->explored = true;
            }
        }

        int calculated_distance;
        int node_towards_origin = calculate_origin_path(matrix, current_node, &calculated_distance);
        if (node_towards_origin == -1) { // Aucun chemin ne peut être calculé
            continue;
        }
        // Si aucun chemin n'a été calculé, ou si la distance n'est pas la même, ou si le prochain noeud n'est pas le même
        if (matrix->nodes[current_node]->towards_origin == NULL
            || calculated_distance != matrix->nodes[current_node]->distance_to_origin
            || node_towards_origin != matrix->nodes[current_node]->towards_origin->from->ID
        ) {
            matrix->nodes[current_node]->distance_to_origin = calculated_distance;
            matrix->nodes[current_node]->towards_origin = matrix->grid[node_towards_origin][current_node];

            // Marquer les voisins pour qu'ils soient recalculés
            for (int i = 0; i < matrix->size; i++) {
                if (matrix->grid[current_node][i] != NULL && !ListContains(node_queue, i)) {
                    ListQueue(node_queue, i);
                }
            }
        }

        
    }
    printf("\n");
    ListFree(node_queue);
    reset_exploration(matrix);
}

ListHead* find_path_to(Matrix* matrix, int node) {
    ListHead* path = ListInit();
    ListQueue(path, node);
    while (node != 0) {
        if (matrix->nodes[node]->towards_origin == NULL) {
            ListFree(path);
            return NULL;
        }
        node = matrix->nodes[node]->towards_origin->from->ID;
        ListQueue(path, node);
    }
    ListReverse(path);
    return path;
}

void print_path(Matrix* matrix, ListHead* path, int* length) {
    ListNode* ptr = path->next;
    while (ptr != NULL) {
        Node* node = matrix->nodes[ptr->data];
        printf("%c%d ", node->type, node->ID);
        *length = node->distance_to_origin;
        ptr = ptr->next;
    }
}

void multiply_matrix(Matrix* matrix, bool* has_changed) {
    /*
    S'il existe un chemin de i vers k, et de k vers j,
    alors on affecte à i->j le chemin i->k

    Si aucun changement n'a été fait, alors has_changed sera mis à false.
    Cela permet d'éviter d'appeler cette fonction de complexité O(n3) inutilement
    */
    *has_changed = false;
    for (int i = 0; i < matrix->size; i++) {
        for (int j = 0; j < matrix->size; j++) {
            if (matrix->grid[i][j] == NULL) {
                for (int k = 0; k < matrix->size; k++) {
                    if (is_usable(matrix->grid[i][k]) && is_usable(matrix->grid[k][j])) {
                        matrix->grid[i][j] = matrix->grid[i][k];
                        *has_changed = true;
                        break;
                    }
                }
            }
        }
    }
}
Matrix* calculate_path_matrix(Matrix* matrix) {
    matrix = copy_matrix_content(matrix); // Copier pour pouvoir appliquer des opérations sans affecter la matrice de départ
    bool has_changed = true;
    for (int i = 0; i < matrix->size && has_changed; i++) {
        multiply_matrix(matrix, &has_changed);
    }
    return matrix;
}
ListHead* find_connected_groups(Matrix* matrix, int* group_count) {
    matrix = calculate_path_matrix(matrix);

    int* _nodes = malloc(matrix->size * sizeof(int));
    for (int i = 0; i < matrix->size; i++) {
        _nodes[i] = i;
    }
    ListHead* nodes = ListFromArray(_nodes, matrix->size); // Liste des noeuds toujours disponibles

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
            if (is_usable(matrix->grid[current_group_base][i->data]) && is_usable(matrix->grid[i->data][current_group_base])) {
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

void mark_secure_roads(Matrix* matrix) {
    int tree_size = 0;
    Node** tree = NULL;
    tree = realloc(tree, (tree_size + 1) * sizeof(Node*));
    if (tree == NULL) {
        printf("Erreur d'alloc\n");
        exit(EXIT_FAILURE);
    }
    tree[tree_size] = matrix->nodes[0];
    tree_size++;

    while(tree_size < matrix->size){ // tant que tout les noeud ne sont pas connectés entres eux 
        int i_min=0;
        int j_min=0;
        for (int i = 0; i < matrix->size; i++){  //chercher la route connecté à tree_ la plus courte et la sécuriser
            if (!is_node_in_array(matrix->nodes[i], tree, tree_size)) {
                continue;
            }

            for (int j = 0; j < matrix->size; j++ ){
                if(matrix->grid[i][j] != NULL){
                    if (matrix->grid[i][j]->to_secure) {
                        continue;
                    }
                    if (matrix->grid[i_min][j_min] == NULL) {
                        i_min = i;
                        j_min = j;
                        continue;
                    }
                    if (matrix->grid[i][j]->distance < matrix->grid[i_min][j_min]->distance && !is_node_in_array(matrix->nodes[j], tree, tree_size)){
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
        tree[tree_size-1] = matrix->nodes[j_min];
        matrix->grid[i_min][j_min]->to_secure = true;
    }

    free(tree);
}

void create_road (Matrix* mat, int A, int B){
    mat->grid[A-1][B-1] = init_road(mat->nodes[A-1], mat->nodes[B-1], 10 , true, 6); // ici distance mise à 10 et capacity à 6 ( à modifier )
    mat->grid[A-1][B-1]->is_created = true;
}

void find_road_to_create(Matrix* matrix){ //Bonus 1
    int created_road = 0 ;
    int number_road_to_create = matrix->size/10; // on set le nombre de route à créer à 1 dixième de la taille du graphe
    while( created_road< number_road_to_create){ // on répete l'action de créer une route jusqu'a que les 10 routes soit crées 
        int i_min=0;
        int j_min=0;
        for (int i = 0; i < matrix->size; i++){
            if (matrix->nodes[i]->connections_out - matrix->nodes[i]->connections_in > matrix->nodes[i_min]->connections_out - matrix->nodes[i_min]->connections_in && matrix->nodes[i]->explored == false){
                i_min = i;
            } // cherche le sommet avec le deltaSortie le plus élevé
        }
        for (int j = 0; j < matrix->size; j++ ){
            if (matrix->nodes[j]->connections_in - matrix->nodes[j]->connections_out > matrix->nodes[j_min]->connections_in - matrix->nodes[j_min]->connections_out && matrix->nodes[j]->explored == false){
                j_min = j;
            }  // cherche le sommet avec le deltaEntrée le plus élevé
        }
        if(matrix->grid[j_min][i_min] == NULL && i_min != j_min){ // si la route entre les 2 sommets n'existe pas encore et que i_min est différent de j_min alors on crée la route
            create_road(matrix, j_min, i_min);
            created_road++;
            printf(" Route %d cree \n" ,created_road);
            reset_exploration(matrix);

        }
        else { // sinon on marque le sommet entré pour dire qu'il n'est pas utilisable pour l'instant
            matrix->nodes[j_min]->explored = true;
        }
    }
    reset_exploration(matrix);
}

void truck_travel() {

}

void citys_is_repared(Matrix* matrix){
    for(int i=0 ; i < matrix->size ; i++){
        if (matrix->node[i]->Is_repared == false ){
            return false;
        }
    }
    return true;

}

void verif_city_reparation(Matrix* matrix){
    for (int i = 0 ; i < matrix->size ; i++){
        if( matrix->node[i]->current_capacity[4] == 100 ){
            matrix->node[i]->Is_repared = true;
        }
    }
}

void repare_city(Matrix* matrix){
    int time = 0;
    while ( citys_is_repared(matrix) != true){ // tant que toute les villes ne sont pas réparés

        // il faut maintenant envoyer des camions pour aprovisioner les villes en matériaux 
        // on verifie si on a des camion libre 
        // si oui on l'envoie ravitailler X ville dans le besoin 
        // On trace son trajet 
        // une fois le camion vide --> retour à la case départ ( ou à l'entrepot le plus proche dans l'idéal )
        // retour à l'étape 1

        // augementer le temps de 1 à chauqe "tick"

        verif_city_reparation(matrix); // actualise l'état des villes 
        time++;
    }
    printf("\n Cela a prit %d tour pour réparer les villes \n " , time);

}

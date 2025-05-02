#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node{
    int ID;
    char type;

}Node;

typedef struct Road{
    // int ID ?
    Node* from;
    Node* to;

    bool direction;

    bool state;

    int current_capacity;
    int max_capacity;
}Road;

typedef struct Data{
    int* node_type_ids;

}Data;

void init_Data(Data* data){
    data->node_type_ids = calloc(3, sizeof(int));
}

void free_data(Data* data){
    free(data->node_type_ids);

    free(data);
}

void print_road(Road* road){
    printf("Road from %s%d to %s%d :\n",
        (road->from->type == 1)? "City" : ((road->from->type == 2)? "Hospital" : "Warehouse"),
        road->from->ID,
        (road->from->type == 1)? "City" : ((road->from->type == 2)? "Hospital" : "Warehouse"),
        road->from->ID);
    printf("  -> State : %s\n", (road->state)? "Destroyed" : "Accessible");
    printf("  -> Current capacity : %d\n", road->current_capacity);
    printf("  -> Maximum capacity : %d\n", road->max_capacity);   
}
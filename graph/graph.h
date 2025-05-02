#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node{
    int ID;
    char type;

    int distance_to_origin;
    int max_capacity_to_origin;
    Road* towards_origin;
}Node;

typedef struct Road{
    // int ID ?
    Node* from;
    Node* to;

    bool direction;
    int distance;
    bool state;

    int current_capacity;
    int max_capacity;
}Road;

typedef struct Variables{
    int* node_type_ids;

}Variables;

void init_Data(Variables* data);

void free_data(Variables* data);

void print_road(Road* road);

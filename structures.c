#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Truck{
    // int ID ?
    
    int current_capacity;
    int max_capacity;
}Truck;

bool can_load_truck(Truck* truck){
    return truck->current_capacity < truck->max_capacity;
}
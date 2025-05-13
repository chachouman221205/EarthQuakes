#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Truck{
    // int ID ?
    
    int current_capacity[5];
    // {Provisions;médicaments;médecins;ouvriers;matériaux}
    int max_capacity;
    int destination;
    int position;
    

}Truck;

bool can_load_truck(Truck* truck){

    return truck->current_capacity < truck->max_capacity;
}
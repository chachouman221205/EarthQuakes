#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "button.h"
//#include "geometry.h"
//#include "../graph/graph.h"

#define BUTTON_COLOR GRAY

//------------------------------------------------------------------------------------
int tkt(void){
    // Initialization
    //--------------------------------------------------------------------------------------
    int w = 2400 * 0.8;
    int h = 1200 * 0.8;
    printf("Début");
    InitWindow(w, h, "EarthQuake");
    printf("Début2");
    
    Rectangle title_bar = {0, 0, w, h/10};
    Rectangle side_bar = {0, title_bar.height, w/4, h};
    int shadow_size = 10;
    Color shadow_color = {0, 0, 0, 150};

    //char* filename;
    //find_file(filename);
    //Variables* var = init_variables();
    //Incidence_Matrix* mat = init_incidence_matrix_from_file(var, filename);
    
    // Buttons
    bool running = false;
    int button_x = side_bar.x + side_bar.width/2;
    int button_width = side_bar.width/2;
    int button_height = h/20;

    Switch start_stop = NewSwitch("start", "stop", button_x, 3*button_height, button_width, button_height, GREEN, RED, &running);
    start_stop.hover_color_off = DARKGREEN;
    start_stop.hover_color_on = MAROON;

    // Main game loop
    while (!WindowShouldClose()){   // close or esc key
        

        BeginDrawing();

            ClearBackground(RAYWHITE);

            //--- Main content ---//
            
            if (running) {
                // ENZO MET TON CODE ICI
                //int** coords_sommets = Coordonate_node(mat, w-side_bar.width, h-title_bar.height, w, h);
            }

            //--- Side Bar ---//
            DrawRectangleRec(side_bar, LIGHTGRAY);

                // Shadow
            DrawRectangleGradientH(side_bar.x + side_bar.width, side_bar.y, shadow_size, side_bar.height, shadow_color, BLANK);
            
                // Buttons
            DrawSwitch(start_stop);

            //--- Title ---//
            DrawRectangleRec(title_bar, GRAY);
            int title_size = 50; char *title = "EarthQuake"; int title_x = title_bar.x + title_bar.width/2; int title_y = title_bar.y + title_bar.height/2;
            DrawText(title,  title_x - strlen(title)*0.3*title_size, title_y - 0.6*title_size, title_size, BLACK);

                // Shadow
            DrawRectangleGradientV(0, title_bar.height, w, shadow_size, shadow_color, BLANK);
            
        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}
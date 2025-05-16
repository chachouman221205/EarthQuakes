#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "button.h"
#include "geometry.h"
#include "../graph/graph.h"

#define BUTTON_COLOR GRAY

//------------------------------------------------------------------------------------
void app_start(char* filename){
    // Initialization
    //--------------------------------------------------------------------------------------
    int w = 2400 * 0.8;
    int h = 1200 * 0.8;
    InitWindow(w, h, filename);
    
    Rectangle title_bar = {0, 0, w, h/10};
    Rectangle side_bar = {0, title_bar.height, w/4, h};
    int shadow_size = 10;
    Color shadow_color = {0, 0, 0, 150};
    
    // Buttons
    bool running = false;
    int button_x = side_bar.x + side_bar.width/2;
    int button_width = side_bar.width/2;
    int button_height = h/20;

    Switch start_stop = NewSwitch("start", "stop", button_x, 3*button_height, button_width, button_height, GREEN, RED, &running);

    bool reset = false;
    Button reset_positions = NewButton("reset positions", button_x, 5*button_height, button_width, button_height, GRAY, &reset);

    bool show_secure = false;
    Switch secure_rodes = NewSwitch("show roads to secure", "hide roads to secure", button_x, 7*button_height, button_width, button_height, GRAY, BLUE, &show_secure);

    Variables* var = init_variables();
    Incidence_Matrix* mat = init_incidence_matrix_from_file(var, filename);

    int** coords_sommets = Coordonate_node(mat, w-side_bar.width, h-title_bar.height, w, h);
    int dragged_node = -1;

    // Main game loop
    while (!WindowShouldClose()){   // close or esc key
        

        BeginDrawing();

            ClearBackground(RAYWHITE);

            //--- Main content ---//
            
            if (running) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // node dragging
                    for (int k = 0; k < mat->size; k++) {
                        if (CheckCollisionPointCircle(GetMousePosition(), (Vector2) {coords_sommets[k][0], coords_sommets[k][1]}, 10)) {
                            dragged_node = k;
                        }
                    }
                }

                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                    dragged_node = -1;
                }

                if (dragged_node != -1) {
                    Vector2 mouse = GetMousePosition();
                    coords_sommets[dragged_node][0] = mouse.x;
                    coords_sommets[dragged_node][1] = mouse.y;
                }



                show(mat, coords_sommets);

                if (reset) {
                    coords_sommets = Coordonate_node(mat, w-side_bar.width, h-title_bar.height, w, h);
                }

                if (show_secure) {
                    mark_secure_roads(mat);
                } else {
                    for (int i = 0; i < mat->size; i++) {
                        for (int j = 0; j < mat->size; j++) {
                            if (mat->grid[i][j] != NULL) {
                                mat->grid[i][j]->to_secure = false;
                            }
                        }
                    }
                }

            }

            //--- Side Bar ---//
            DrawRectangleRec(side_bar, LIGHTGRAY);

                // Shadow
            DrawRectangleGradientH(side_bar.x + side_bar.width, side_bar.y, shadow_size, side_bar.height, shadow_color, BLANK);
            
                // Buttons
            DrawSwitch(start_stop);
            DrawButton(reset_positions);
            DrawSwitch(secure_rodes);

            //--- Title ---//
            DrawRectangleRec(title_bar, GRAY);
            int title_size = 50; char *title = "EarthQuakeSim"; int title_x = title_bar.x + title_bar.width/2; int title_y = title_bar.y + title_bar.height/2;
            DrawText(title,  title_x - strlen(title)*0.3*title_size, title_y - 0.6*title_size, title_size, BLACK);

                // Shadow
            DrawRectangleGradientV(0, title_bar.height, w, shadow_size, shadow_color, BLANK);
            
        EndDrawing();
    }

    CloseWindow();

    free_incidence_matrix_content(mat);
    free_incidence_matrix(mat);
    free_variables_struct(var);
}

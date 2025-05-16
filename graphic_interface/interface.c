#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "button.h"
#include "geometry.h"
#include "../graph/graph.h"
#include "raylib_utils.h"

#define BUTTON_COLOR GRAY

//------------------------------------------------------------------------------------
void app_start(char* filename){
    // Initialization
    //--------------------------------------------------------------------------------------
    int w = 2400 * 0.8;
    int h = 1200 * 0.8;
    InitWindow(w, h, filename);
    
    Rectangle title_bar = {0, 0, w, h/10};
    Rectangle side_bar = {0, title_bar.height, w/3, h};
    Rectangle draw_area = {side_bar.width, title_bar.height, w-side_bar.width, h-title_bar.height};
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

    bool earth_quake = false;
    Button trigger_EQ = NewButton("make an earth quake", button_x, 7*button_height, button_width, button_height, GRAY, &earth_quake);

    bool show_secure = false;
    Switch secure_roads = NewSwitch("show roads to secure", "hide roads to secure", button_x, 9*button_height, button_width, button_height, GRAY, BLUE, &show_secure);

    bool find_connected_nodes = false;
    Switch find_connected_nodes_button = NewSwitch("find all nodes of a group", "cancel", button_x, 11*button_height, button_width, button_height, GRAY, brightness(RED, 1), &find_connected_nodes);

    Variables* var = init_variables();
    Incidence_Matrix* mat = init_incidence_matrix_from_file(var, filename);

    int** coords_sommets = Coordonate_node(mat, w-side_bar.width, h-title_bar.height, w, h);
    int dragged_node = -1;
    int n_group;
    ListHead* groups;

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

                // correction des nodes en dehors de l'espace
                for (int k = 0; k < mat->size; k++) {
                    if (coords_sommets[k][0] < draw_area.x) {
                        coords_sommets[k][0] = draw_area.x;
                    }
                    if (coords_sommets[k][0] > draw_area.x + draw_area.width) {
                        coords_sommets[k][0] = draw_area.x + draw_area.width;
                    }
                    if (coords_sommets[k][1] < draw_area.y) {
                        coords_sommets[k][1] = draw_area.y;
                    }
                    if (coords_sommets[k][1] > draw_area.y + draw_area.height) {
                        coords_sommets[k][1] = draw_area.y + draw_area.height;
                    }
                }


                update_accessibility(mat);


                show(mat, coords_sommets);

                if (reset) {
                    coords_sommets = Coordonate_node(mat, w-side_bar.width, h-title_bar.height, w, h);
                }

                if (earth_quake) {
                    Earthquake(mat);
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

                if (find_connected_nodes){
                    DrawRectangleV(GetMousePosition(), (Vector2) {180, 40}, TOOL_TIP_COLOR);
                    DrawText("Hover over a point to\nsee all connected nodes", GetMousePosition().x + 20, GetMousePosition().y, 10, WHITE);
                    for (int i = 0; i < mat->size; i++) {
                        if (CheckCollisionPointCircle(GetMousePosition(), (Vector2) {coords_sommets[i][0], coords_sommets[i][1]}, 10)) {
                            // find group of points

                            groups = find_connected_groups(mat, &n_group);
                            for (int j = 0; j < n_group; j++) {
                                if (ListContains(&groups[j], i)) {
                                    draw_group(coords_sommets, &groups[j]);
                                }
                            }
                        }
                    }
                }
            } else {
                // Reset de la simulation

                free_incidence_matrix_content(mat);
                free_incidence_matrix(mat);
                free_variables_struct(var);

                var = init_variables();
                mat = init_incidence_matrix_from_file(var, filename);

                coords_sommets = Coordonate_node(mat, w-side_bar.width, h-title_bar.height, w, h);
            }

            //--- Side Bar ---//
            DrawRectangleRec(side_bar, LIGHTGRAY);

                // Shadow
            DrawRectangleGradientH(side_bar.x + side_bar.width, side_bar.y, shadow_size, side_bar.height, shadow_color, BLANK);
            
                // Buttons
            DrawSwitch(start_stop);
            DrawButton(trigger_EQ);
            DrawButton(reset_positions);
            DrawSwitch(secure_roads);
            DrawSwitch(find_connected_nodes_button);

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

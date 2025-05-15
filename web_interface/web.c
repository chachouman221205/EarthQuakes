#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "button.h"

#define BUTTON_COLOR GRAY

//------------------------------------------------------------------------------------
int main(void){
    // Initialization
    //--------------------------------------------------------------------------------------
    int w = 2400 * 0.8;
    int h = 1200 * 0.8;
    InitWindow(w, h, "EarthQuake");
    
    Rectangle side_bar = { 0, 0, w/4, h};
    
    // Buttons
    bool button_click = false;
    int button_x = side_bar.x + side_bar.width/2;
    int button_width = side_bar.width/2;
    int button_height = h/20;

    // Main game loop
    while (!WindowShouldClose()){   // close or esc key
        Vector2 mousePos = GetMousePosition();
        //bool hover = CheckCollisionPointRec(mousePos, button);
        //bool click = hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        
        Button start_button = NewButton("Mission1", button_x, 3*button_height, button_width, button_height, BUTTON_COLOR, NULL);
        start_button.hover_color = DARKGRAY;

        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            //--- Side Bar ---//
            DrawRectangleRec(side_bar, LIGHTGRAY);
            
                // Title
            int title_x = w/8; int title_y = h/20; int title_size = 50; char *title = "EarthQuake";
            DrawText(title,  title_x - strlen(title)*0.3*title_size, title_y - 0.6*title_size, title_size, BLACK);
            
                // Buttons
            DrawButton(start_button);

            //--- Main content ---//
            

        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}
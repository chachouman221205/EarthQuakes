#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------------
int main(void){
    // Initialization
    //--------------------------------------------------------------------------------------
    int w = 2400 * 0.8;
    int h = 1200 * 0.8;
    InitWindow(w, h, "raylib [core] example - basic window");
    
    Rectangle button = { 350, 200, 100, 50 };
    bool buttonClicked = false;

    // Main game loop
    while (!WindowShouldClose()){   // close or esc key
        Vector2 mousePos = GetMousePosition();
        bool hover = CheckCollisionPointRec(mousePos, button);
        bool click = hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        if(click) {
            buttonClicked = true;
        }
    
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            DrawRectangleRec(button, hover ? DARKGRAY : GRAY);

            char text[100] = "aaaaaaaaaaaaa";
            int size = 20;
            DrawText(text, w/2 - strlen(text)*0.3*size, h/2 - 0.6*size, size, BLACK);
            
            if(buttonClicked) {
                DrawText("Bouton cliqué !", 330, 300, 20, RED);
            }

        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}
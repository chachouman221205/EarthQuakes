#include <string.h>
#include <stdio.h>

#include "raylib.h"

#define ROUNDNESS 0.4f

typedef struct Button {
    char text[50];
    int x;
    int y;
    int size_x;
    int size_y;
    Rectangle rec;
    Color color;
    Color hover_color;
    bool* clicked;
} Button;

void DrawButton(Button button) {
    Vector2 mousePos = GetMousePosition();
    bool hover = CheckCollisionPointRec(mousePos, button.rec);
    DrawRectangleRounded(button.rec, ROUNDNESS, 8, hover ? button.hover_color : button.color);
    DrawRectangleRoundedLines(button.rec, ROUNDNESS, 8, BLACK);
    int size = 20;
    DrawText(button.text, button.x - strlen(button.text)*0.3*size, button.y-0.6*size, size, BLACK);
}

Button NewButton(char text[50], int x, int y, int size_x, int size_y, Color color, bool* clicked) {
    Button button;
    strcpy(button.text, text);
    button.x = x;
    button.y = y;
    button.size_x = size_x;
    button.size_y = size_y;
    button.rec = (Rectangle) {button.x-button.size_x/2, button.y-button.size_y/2, button.size_x, button.size_y};
    button.color = color;
    button.clicked = clicked;
    return button;
}

Button NewButtonRec(char text[50], Rectangle rec, Color color, bool* clicked) {
    Button button;
    strcpy(button.text, text);
    button.x = rec.x + rec.width/2;
    button.y = rec.y + rec.height/2;
    button.size_x = rec.width;
    button.size_y = rec.height;
    button.rec = rec;
    button.color = color;
    button.clicked = clicked;
    return button;
}
#include <string.h>

#include "raylib.h"

#define ROUNDNESS 0.4f

typedef struct Button {
    char text[50];
    int x;
    int y;
    int size_x;
    int size_y;
    Color color;
    bool* clicked;
} Button;

void DrawButton(Button button) {
    Rectangle rec = {button.x-button.size_x/2, button.y-button.size_y/2, button.size_x, button.size_y};
    DrawRectangleRounded(rec, ROUNDNESS, 8, button.color);
    DrawRectangleRoundedLines(rec, ROUNDNESS, 8, BLACK);
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
    button.color = color;
    button.clicked = clicked;
    return button;
}
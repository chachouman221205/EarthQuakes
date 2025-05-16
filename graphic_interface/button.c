#include <string.h>
#include <stdio.h>

#include "raylib.h"

#define ROUNDNESS 0.4f

Color brightness(Color col, float brightness){
    int r = (int) col.r * brightness;
    int g = (int) col.g * brightness;
    int b = (int) col.b * brightness;

    return (Color) {r,g,b,col.a};
}

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
    if (button.clicked != NULL) *(button.clicked) = hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

Button NewButton(char* text, int x, int y, int size_x, int size_y, Color color, bool* clicked) {
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

Button NewButtonRec(char* text, Rectangle rec, Color color, bool* clicked) {
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


typedef struct Switch {
    char text_off[50];
    char text_on[50];
    int x;
    int y;
    int size_x;
    int size_y;
    Rectangle rec;
    Color color_off;
    Color color_on;
    bool* state;
} Switch;

void DrawSwitch(Switch s) {
    Vector2 mousePos = GetMousePosition();
    bool hover = CheckCollisionPointRec(mousePos, s.rec);
    Color col;
    char* t;
    if (*(s.state)) {
        col = hover ? brightness(s.color_on, 0.7) : s.color_on;
        t = s.text_on;
    } else {
        col = hover ? brightness(s.color_off, 0.7) : s.color_off;
        t = s.text_off;
    }
    DrawRectangleRounded(s.rec, ROUNDNESS, 1, col);
    DrawRectangleRoundedLines(s.rec, ROUNDNESS, 1, BLACK);
    int size = 20;
    DrawText(t, s.x - strlen(t)*0.3*size, s.y-0.6*size, size, BLACK);
    
    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (hover) {
            *(s.state) = !(*(s.state));
        }
    }
}


Switch NewSwitch(char* text_off, char* text_on, int x, int y, int size_x, int size_y, Color color_off, Color color_on, bool* state) {
    Switch s;
    strcpy(s.text_on, text_on);
    strcpy(s.text_off, text_off);
    s.x = x;
    s.y = y;
    s.size_x = size_x;
    s.size_y = size_y;
    s.rec = (Rectangle) {s.x-s.size_x/2, s.y-s.size_y/2, s.size_x, s.size_y};
    s.color_on = color_on;
    s.color_off = color_off;
    s.state = state;
    return s;
}

#include "raylib.h"

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

void DrawButton(Button button);
Button NewButton(char text[50], int x, int y, int size_x, int size_y, Color color, bool* clicked);
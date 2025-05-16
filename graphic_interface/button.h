#include "raylib.h"

#define TOOL_TIP_COLOR ((Color) {0,0,0,150})


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
Button NewButton(char* text, int x, int y, int size_x, int size_y, Color color, bool* clicked);

typedef struct Switch {
    char text_off[50];
    char text_on[50];
    int x;
    int y;
    int size_x;
    int size_y;
    Rectangle rec;
    Color color_off;
    Color hover_color_off;
    Color color_on;
    Color hover_color_on;
    bool* state;
} Switch;

void DrawSwitch(Switch s);
Switch NewSwitch(char* text_on, char* text_off, int x, int y, int size_x, int size_y, Color color_on, Color color_off, bool* state);

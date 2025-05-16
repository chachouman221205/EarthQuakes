#include "raylib.h"
#include "math.h"

float norm(Vector2 vec) {
    return sqrt(vec.x*vec.x + vec.y*vec.y);
}

Vector2 normalize(Vector2 vec) {
    float vec_norm = norm(vec);
    return (Vector2) {vec.x/vec_norm, vec.y/vec_norm};
}

Vector2 scale(Vector2 vec, float length) {
    float vec_norm = norm(vec);
    return (Vector2) {vec.x/vec_norm * length, vec.y/vec_norm * length};
}

Vector2 rotate(Vector2 vec, int angle) {
    float c = cos(angle);
    float s = sin(angle);
    return (Vector2) {
        c*vec.x - s*vec.y,
        s*vec.x + c*vec.y
    };
}


Color brightness(Color col, float brightness){
    int r = (int) col.r * brightness;
    int g = (int) col.g * brightness;
    int b = (int) col.b * brightness;

    return (Color) {r,g,b,col.a};
}

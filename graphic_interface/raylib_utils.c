#include "raylib.h"
#include "math.h"

float norm(Vector2 vec) {
    return sqrt(vec.x*vec.x + vec.y*vec.y);
}

Vector2 normalize(Vector2 vec) {
    float vec_norm = norm(vec);
    return (Vector2) {vec.x/vec_norm, vec.y/vec_norm};
}

Vector2 rotate(Vector2 vec, int angle) {
    float c = cos(angle);
    float s = sin(angle);
    return (Vector2) {
        c*vec.x - s*vec.y,
        s*vec.x + c*vec.y
    };
}

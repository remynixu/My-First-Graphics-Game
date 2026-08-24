#include "types.h"

struct vector2 tovec2(int x, int y){
    struct vector2 vec2;
    {
        vec2.x = x;
        vec2.y = y;
    }
    return vec2;
}
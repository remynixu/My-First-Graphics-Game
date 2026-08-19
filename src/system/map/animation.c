#include "animation.h"

static float _time = 0.0f;

void update_animation_time(float delta_time){
    if(_time >= 1.0f)
        _time = 0.0f;
    _time += delta_time;
}

int get_animation_frame(int fps){
    return (int)(_time * (float)fps);
}
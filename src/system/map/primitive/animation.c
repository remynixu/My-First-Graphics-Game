#include "animation.h"

static float _time = 0.0f;

/*
 * NOTICE:
 * 
 * This HOUR macro serves to delay a bug that ruins animations when this timer
 * resets back to zero while the animation occurs.
 */

#define HOUR    (float)(60 * 60)

void update_animation_time(float delta_time){
    if(delta_time <= 0.0f){
        _time = 0.0f;
        return;
    }
    if(_time >= HOUR)
        _time = 0.0f;
    _time += delta_time;
}

#include "math.h"

int get_animation_frame(float fps, float duration){
    return (int)(fmod(_time, duration) * fps);
}
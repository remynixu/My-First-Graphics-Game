#include "engine.h"

#include <raylib.h>
#include <stdio.h>

int engine_init(struct engine_ctx *hint){
    if(!ChangeDirectory(GetApplicationDirectory()))
        return -1;
    InitWindow(hint->screen_width, hint->screen_height, "Inchoatus");
    SetTargetFPS(hint->target_fps);
    hint->state = ENGINE_STATE_RUNNING;
    return 0;
}

static const char errstr[][24] = {
    "[ENGINE]:SUCCESS",
    "[ENGINE]:DIRECTORY_FAIL"
};

void engine_perror(int errcode){
    puts(errstr[-errcode]);
}

void engine_update(struct engine_ctx *ctx){
    if(WindowShouldClose()){
        ctx->state = ENGINE_STATE_QUIT;
        return;
    }
    ctx->delta_time = GetFrameTime();
}

void engine_close(void){
    CloseWindow();
}
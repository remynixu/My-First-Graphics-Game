#include "engine.h"

#include "core/renderer.h"
#include "core/tile.h"

#include <raylib.h>

int engine_init(struct engine_ctx *ctx, struct engine_hint *hint){
    if(renderer_init(&hint->screen))
        return -1;
    renderer_clean(&ctx->renderer_ctx);
    if(tile_init())
        return -2;
    {
        ctx->state = ENGINE_STATE_RUNNING;
        ctx->screen = hint->screen;
    }
    return 0;
}

void engine_update(struct engine_ctx *ctx){
    if(WindowShouldClose()){
        ctx->state = ENGINE_STATE_QUIT;
        return;
    }
    ctx->delta_time = GetFrameTime();
}

void engine_render(struct engine_ctx *ctx){
    renderer_flush(&ctx->renderer_ctx, &ctx->screen);
}

void engine_close(void){
    renderer_quit();
    tile_quit();
}
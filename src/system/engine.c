#include "engine.h"

#include "core/renderer.h"
#include "core/screen.h"
#include "core/tile.h"

#include <raylib.h>

int engine_init(struct engine_ctx *ctx, struct engine_hint *hint){
    if(screen_init(&ctx->main_screen, &hint->window))
        return -1;
    if(tile_init())
        return -2;
    {
        renderer_clean(&ctx->renderer_buf);
        SetTargetFPS(hint->target_fps);
    }
    {
        ctx->state = ENGINE_STATE_RUNNING;
        ctx->window = hint->window;
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
    renderer_command cmd;
    struct tile t;
    { /* tile */
        t.state = TILE_NORMAL;
        t.type = TILE_NULL;
        t.x = ctx->window.width / 2;
        t.y = ctx->window.height / 2;
    }
    { /* cmd */
        cmd = tile_gettex(&t);
    }
    renderer_push(&ctx->renderer_buf, &cmd);
    screenmode_begin(&ctx->main_screen);
    {
        renderer_flush(&ctx->renderer_buf);
    }
    screenmode_end();
    screen_update(&ctx->main_screen);
}

#include <stdio.h>

void engine_perror(void){
    perror(GetApplicationDirectory());
}

void engine_close(struct engine_ctx *ctx){
    screen_quit(&ctx->main_screen);
    window_quit();
    tile_quit();
}
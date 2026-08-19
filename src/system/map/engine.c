#include "engine.h"

void start_engine(struct engine_ctx *ctx, const char *title){
    InitWindow(ctx->screen.width, ctx->screen.height, title);
    SetTargetFPS(ctx->target_fps);
}

static void _update_heldkey_flags(struct engine_ctx *ctx){
    ctx->heldkey_flags = 0;
    if(IsKeyDown(KEY_W))
        ctx->heldkey_flags |= KEYCODE_W;
    if(IsKeyDown(KEY_S))
        ctx->heldkey_flags |= KEYCODE_S;
    if(IsKeyDown(KEY_A))
        ctx->heldkey_flags |= KEYCODE_A;
    if(IsKeyDown(KEY_D))
        ctx->heldkey_flags |= KEYCODE_D;
    if(IsKeyDown(KEY_SPACE))
        ctx->heldkey_flags |= KEYCODE_SPC;
    if(IsKeyDown(KEY_Q))
        ctx->heldkey_flags |= KEYCODE_Q;
    if(IsKeyDown(KEY_F))
        ctx->heldkey_flags |= KEYCODE_F;
    if(IsKeyDown(KEY_R))
        ctx->heldkey_flags |= KEYCODE_R;
}

void update_engine(struct engine_ctx *ctx){
    ctx->time.delta = GetFrameTime();
    ctx->time.animation += ctx->time.delta;
    if(ctx->time.animation >= 1.0f)
        ctx->time.animation = 0;
    tile_animation_time = ctx->time.animation;
    _update_heldkey_flags(ctx);
}

void end_engine(void){
    CloseWindow();
}
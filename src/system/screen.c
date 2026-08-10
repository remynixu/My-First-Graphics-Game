#include "screen.h"

void setup_screen(struct engine_ctx *ctx, struct screen *scr){
    scr->target = LoadRenderTexture(ctx->screen.width, ctx->screen.height);
    scr->src.width = (float)scr->target.texture.width;
    scr->src.height = -(float)scr->target.texture.height;
    scr->dst.width = ctx->screen.width;
    scr->dst.height = ctx->screen.height;
}

void draw_screen(struct screen *scr){
    Vector2 origin = {0};
    DrawTexturePro(scr->target.texture, scr->src, scr->dst, origin, 0.0f, WHITE);
}

void end_screen(struct screen *scr){
    UnloadRenderTexture(scr->target);
}
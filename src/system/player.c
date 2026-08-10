#include "player.h"

void setup_player(int spawn_x, int spawn_y, struct player *p){
        p->display.pos.x = spawn_x;
        p->display.pos.y = spawn_y;
        p->display.type = ENTITY_PLAYER;
        p->display.scale = 1.0f;
        p->speed = 50.0f;
}

void update_player(struct engine_ctx *ctx, struct player *p){
    float move = p->speed * ctx->delta_time;
    if(ctx->heldkey_flags & KEYCODE_W)
        p->display.pos.y -= move;
    if(ctx->heldkey_flags & KEYCODE_S)
        p->display.pos.y += move;
    if(ctx->heldkey_flags & KEYCODE_A)
        p->display.pos.x -= move;
    if(ctx->heldkey_flags & KEYCODE_D)
        p->display.pos.x += move;
}
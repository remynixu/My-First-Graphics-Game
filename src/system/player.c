#include "player.h"

void setup_player(int spawn_x, int spawn_y, struct player *p){
        p->display.pos.x = spawn_x;
        p->display.pos.y = spawn_y;
        p->display.type = ENTITY_PLAYER;
        p->display.scale = 1.0f;
        p->speed = 50.0f;
}

#include "collision.h"

void update_player(struct engine_ctx *ctx, struct player *p){
    char face_flag = 0;
    float move = p->speed * ctx->delta_time;
    float boing = 5.0f;
    float new_x = p->display.pos.x;
    float new_y = p->display.pos.y;
    if(ctx->heldkey_flags & KEYCODE_W){
        face_flag |= (1 << 0);
        new_y -= move;
    }
    if(ctx->heldkey_flags & KEYCODE_S){
        face_flag |= (1 << 1);
        new_y += move;
    }
    if(ctx->heldkey_flags & KEYCODE_A){
        face_flag |= (1 << 2);
        new_x -= move;
    }
    if(ctx->heldkey_flags & KEYCODE_D){
        face_flag |= (1 << 3);
        new_x += move;
    }
    if(check_collision(&p->display, ctx->curr_chunk)){
        if(face_flag & (1 << 0))
            new_y += move * boing;
        if(face_flag & (1 << 1))
            new_y -= move * boing;
        if(face_flag & (1 << 2))
            new_x += move * boing;
        if(face_flag & (1 << 3))
            new_x -= move * boing;
    }
    p->display.pos.x = new_x;
    p->display.pos.y = new_y;
}
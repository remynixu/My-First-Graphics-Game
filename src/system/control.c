#include "control.h"
#include "collision.h"

static void _move_ent(struct engine_ctx *ctx, struct entity *e){
    float speed = (float)e->speed * ctx->delta_time;
    if(ctx->heldkey_flags & KEYCODE_A){
        e->direction = ENTITY_LEFT;
        e->pos.x -= speed;
        if(check_etoc_collision(e, ctx->game.curr_chunk))
            e->pos.x += speed;
        if(check_etoe_collision(e, ctx->game.entity_list))
            e->pos.x += speed;
    }
    if(ctx->heldkey_flags & KEYCODE_D){
        e->direction = ENTITY_RIGHT;
        e->pos.x += speed;
        if(check_etoc_collision(e, ctx->game.curr_chunk))
            e->pos.x -= speed;
        if(check_etoe_collision(e, ctx->game.entity_list))
            e->pos.x -= speed;
    }
    speed *= (float)TILE_PIXEL_HEIGHT / (float)TILE_PIXEL_WIDTH;
    if(ctx->heldkey_flags & KEYCODE_S){
        e->direction = ENTITY_DOWN;
        e->pos.y += speed;
        if(check_etoc_collision(e, ctx->game.curr_chunk))
            e->pos.y -= speed;
        if(check_etoe_collision(e, ctx->game.entity_list))
            e->pos.y -= speed;
    }
    if(ctx->heldkey_flags & KEYCODE_W){
        e->direction = ENTITY_UP;
        e->pos.y -= speed;
        if(check_etoc_collision(e, ctx->game.curr_chunk))
            e->pos.y += speed;
        if(check_etoe_collision(e, ctx->game.entity_list))
            e->pos.y += speed;
    }
}

void control_entity(struct engine_ctx *ctx, struct entity *e){
    if(!ctx->heldkey_flags)
        return;
    _move_ent(ctx, e);
}
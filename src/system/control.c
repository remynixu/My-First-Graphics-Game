#include "control.h"
#include "collision.h"

static void _move_ent(struct engine_ctx *ctx, struct entity *e){
    if(ctx->heldkey_flags & KEYCODE_S){
        e->direction = ENTITY_UP;
        e->pos.y += (float)e->speed * ctx->delta_time;
        if(check_etoc_collision(e, ctx->curr_chunk))
            e->pos.y -= (float)e->speed * ctx->delta_time;
    }
    if(ctx->heldkey_flags & KEYCODE_W){
        e->direction = ENTITY_DOWN;
        e->pos.y -= (float)e->speed * ctx->delta_time;
        if(check_etoc_collision(e, ctx->curr_chunk))
            e->pos.y += (float)e->speed * ctx->delta_time;
    }
    if(ctx->heldkey_flags & KEYCODE_A){
        e->direction = ENTITY_LEFT;
        e->pos.x -= (float)e->speed * ctx->delta_time;
        if(check_etoc_collision(e, ctx->curr_chunk))
            e->pos.x += (float)e->speed * ctx->delta_time;
    }
    if(ctx->heldkey_flags & KEYCODE_D){
        e->direction = ENTITY_RIGHT;
        e->pos.x += (float)e->speed * ctx->delta_time;
        if(check_etoc_collision(e, ctx->curr_chunk))
            e->pos.x -= (float)e->speed * ctx->delta_time;
    }
}

void control_entity(struct engine_ctx *ctx, struct entity *e){
    if(!ctx->heldkey_flags)
        return;
    _move_ent(ctx, e);
}
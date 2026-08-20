#include "control.h"
#include "collision.h"

#define DIAGONAL_MULTIPLIER 0.75f

static void _move_ent(struct engine_ctx *ctx, struct entity *e){
    float x_speed = (float)e->speed * ctx->delta_time;
    float y_speed = x_speed * ((float)TILE_PIXEL_HEIGHT / (float)TILE_PIXEL_WIDTH);
    unsigned char flags = ctx->heldkey_flags;
    Vector2 next_pos = {0};
    if(flags & KEYCODE_A){
        e->direction = ENTITY_LEFT;
        next_pos.x -= x_speed;
    }
    if(flags & KEYCODE_D){
        e->direction = ENTITY_RIGHT;
        next_pos.x += x_speed;
    }
    if(flags & KEYCODE_W){
        e->direction = ENTITY_UP;
        next_pos.y -= y_speed;
    }
    if(flags & KEYCODE_S){
        e->direction = ENTITY_DOWN;
        next_pos.y += y_speed;
    }
    if(next_pos.x != 0.0f && next_pos.y != 0.0f){
        next_pos.x *= DIAGONAL_MULTIPLIER;
        next_pos.y *= DIAGONAL_MULTIPLIER;
    }
    /* INCOMPLETE SUPPORT!!!
    if(flags & (KEYCODE_W | KEYCODE_D))
        e->direction = ENTITY_UPRIGHT;
    if(flags & (KEYCODE_S | KEYCODE_D))
        e->direction = ENTITY_DOWNRIGHT;
    if(flags & (KEYCODE_W | KEYCODE_A))
        e->direction = ENTITY_UPLEFT;
    if(flags & (KEYCODE_W | KEYCODE_A))
        e->direction = ENTITY_UPLEFT;
    */
    {
        e->pos.x += next_pos.x;
        if(check_etoc_collision(e, ctx->game.curr_chunk))
            e->pos.x -= next_pos.x;
        if(check_etoe_collision(e, ctx->game.entity_list))
            e->pos.x -= next_pos.x;
    }
    {
        e->pos.y += next_pos.y;
        if(check_etoc_collision(e, ctx->game.curr_chunk))
            e->pos.y -= next_pos.y;
        if(check_etoe_collision(e, ctx->game.entity_list))
            e->pos.y -= next_pos.y;
    }
}

void control_entity(struct engine_ctx *ctx, struct entity *e){
    if(!ctx->heldkey_flags)
        return;
    _move_ent(ctx, e);
}
#include "game.h"

void game_init(struct game_state *gs){
    InitWindow(gs->screen_width, gs->screen_height, GAME_TITLE);
    SetTargetFPS(gs->target_fps);
}

void game_cleanup(void){
    CloseWindow();
}

static void _update_heldkey_flags(struct game_state *gs){
    gs->heldkey_flags = 0;
    if(IsKeyDown(KEY_W))
        gs->heldkey_flags |= KEYCODE_W;
    if(IsKeyDown(KEY_S))
        gs->heldkey_flags |= KEYCODE_S;
    if(IsKeyDown(KEY_A))
        gs->heldkey_flags |= KEYCODE_A;
    if(IsKeyDown(KEY_D))
        gs->heldkey_flags |= KEYCODE_D;
    if(IsKeyDown(KEY_SPACE))
        gs->heldkey_flags |= KEYCODE_SPC;
    if(IsKeyDown(KEY_Q))
        gs->heldkey_flags |= KEYCODE_Q;
    if(IsKeyDown(KEY_F))
        gs->heldkey_flags |= KEYCODE_F;
    if(IsKeyDown(KEY_R))
        gs->heldkey_flags |= KEYCODE_R;
}

void update_gamestate(struct game_state *gs){
    gs->delta_time = GetFrameTime();
    _update_heldkey_flags(gs);
}
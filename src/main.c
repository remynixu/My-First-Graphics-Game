#include "game/game.h"
#include "game/map.h"

int main(void){
    struct game_state game_state;
    struct map map;
    if(!ChangeDirectory(GetApplicationDirectory()))
        return -1;
    game_state.screen_height = 450;
    game_state.screen_width = 800;
    game_state.target_fps = 60;
    init_game(&game_state);
    /* TEST MAP */
    if(init_map(&map, ftov(200, 200), ftov(0, 0), "assets/null_texture.png", 16.0f))
        return -1;
    while(!WindowShouldClose()){
        update_gamestate(&game_state);
        if(game_state.heldkey_flags & KEYCODE_W)
            map.camera.y -= 0.5f * game_state.delta_time;
        if(game_state.heldkey_flags & KEYCODE_S)
            map.camera.y += 0.5f * game_state.delta_time;
        if(game_state.heldkey_flags & KEYCODE_A)
            map.camera.x -= 0.5f * game_state.delta_time;
        if(game_state.heldkey_flags & KEYCODE_D)
            map.camera.x += 0.5f * game_state.delta_time;
        BeginDrawing();
        {
            ClearBackground(DARKGRAY); 
            draw_map(&map);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
    cleanup_map(&map);
    cleanup_game();
    return 0;
}

#include "game/game.h"
#include "game/map.h"

int main(void){
    struct game_state game_state;
    /* TEST MAP */
    struct map map;
    struct map_cam map_cam;
    struct map_tex map_tex;
    if(!ChangeDirectory(GetApplicationDirectory()))
        return -1;
    game_state.screen_height = 450;
    game_state.screen_width = 800;
    game_state.target_fps = 60;
    init_game(&game_state);
    /* TEST MAP */
    map_cam.pos = ftov(0, 0);
    map_cam.speed = 300;
    map_tex.tex_scale = 16;
    if(init_map(&map, ftov(0, 0), map_cam, "assets/null_texture.png", map_tex))
        return -1;
    while(!WindowShouldClose()){
        update_gamestate(&game_state);
        if(game_state.heldkey_flags & KEYCODE_W)
            map.cam.pos.y -= map.cam.speed * game_state.delta_time;
        if(game_state.heldkey_flags & KEYCODE_S)
            map.cam.pos.y += map.cam.speed * game_state.delta_time;
        if(game_state.heldkey_flags & KEYCODE_A)
            map.cam.pos.x -= map.cam.speed * game_state.delta_time;
        if(game_state.heldkey_flags & KEYCODE_D)
            map.cam.pos.x += map.cam.speed * game_state.delta_time;
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

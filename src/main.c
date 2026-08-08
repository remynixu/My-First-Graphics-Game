#include "system/game.h"
#include "system/chunk.h"

struct game_state game_state = {0};

void init(void){
    game_state.screen_height = 450;
    game_state.screen_width = 800;
    game_state.target_fps = 60;
    init_game(&game_state);
}

struct chunk chunk = {0};

int main(void){
    if(!ChangeDirectory(GetApplicationDirectory()))
        return -1;
    init();
    if(load_tile_textures() != 0)
        return -2;
    if(parse_chunk("assets/chunks/test.chunk", &chunk) != 0)
        return -3;
    while(!WindowShouldClose()){
        update_gamestate(&game_state);
        BeginDrawing();
        {
            ClearBackground(DARKGRAY); 
            draw_chunk(&chunk);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
    free_tile_textures();
    cleanup_game();
    return 0;
}

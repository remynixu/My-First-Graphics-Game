#include "system/game.h"
#include "system/tile.h"

struct game_state game_state;

void init(void){
    game_state.screen_height = 450;
    game_state.screen_width = 800;
    game_state.target_fps = 60;
    init_game(&game_state);
}

struct tile tile = {0};

int main(void){
    if(!ChangeDirectory(GetApplicationDirectory()))
        return -1;
    init();
    /* TILE TEST */
    tile.type = TILE_NULL;
    tile.x = 16;
    tile.y = 16;
    if(load_tile(&tile) != 0)
        return -1;
    while(!WindowShouldClose()){
        update_gamestate(&game_state);
        BeginDrawing();
        {
            ClearBackground(DARKGRAY); 
            /* TILE TEST */
            draw_tile(&tile);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
    /* TILE TEST */
    free_tile(&tile);
    cleanup_game();
    return 0;
}

#include "game/game.h"
#include "game/entity.h"

void init(struct game_state *gs){
    gs->screen_height = 450;
    gs->screen_width = 800;
    gs->target_fps = 60;
    game_init(gs);
}

int main(void){
    struct game_state game_state;
    init(&game_state);
    while(!WindowShouldClose()){
        update_gamestate(&game_state);
        BeginDrawing();
        {
            ClearBackground(DARKGRAY); 
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
    game_cleanup();
    return 0;
}

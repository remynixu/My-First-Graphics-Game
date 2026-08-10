#include "system/game.h"
#include "system/chunk.h"

struct game_state game_state = {0};
struct chunk chunk = {0};
RenderTexture2D game_target = {0};

void init(void){
    game_state.screen_height = 450;
    game_state.screen_width = 800;
    game_state.target_fps = 60;
    init_game(&game_state);
    game_target = LoadRenderTexture(game_state.screen_width, game_state.screen_height);
}

int main(void){
    Rectangle src_rec = {0}, dest_rec = {0};
    Vector2 origin = {0};
    Camera2D cam = {0};
    if(!ChangeDirectory(GetApplicationDirectory()))
        return -1;
    init();
    if(load_tile_textures() != 0)
        return -2;
    if(parse_chunk("assets/chunks/test.chunk", &chunk) != 0)
        return -3;
    src_rec.width = (float)game_target.texture.width;
    src_rec.height = -(float)game_target.texture.height;
    dest_rec.width = game_state.screen_width;
    dest_rec.height = game_state.screen_height;
    cam.zoom = 1.0f;
    while(!WindowShouldClose()){
        float cam_move;
        update_gamestate(&game_state);
        cam_move = 400.0f * game_state.delta_time;
        if(game_state.heldkey_flags & KEYCODE_W)
            cam.target.y -= cam_move;
        if(game_state.heldkey_flags & KEYCODE_S)
            cam.target.y += cam_move;
        if(game_state.heldkey_flags & KEYCODE_A)
            cam.target.x -= cam_move;
        if(game_state.heldkey_flags & KEYCODE_D)
            cam.target.x += cam_move;
        BeginTextureMode(game_target);
        {
            ClearBackground(DARKGRAY);
            BeginMode2D(cam);
            {
                draw_chunk(&chunk);
            }
            EndMode2D();
        }
        EndTextureMode();
        BeginDrawing();
        {
            ClearBackground(BLACK); 
            DrawTexturePro(game_target.texture, src_rec, dest_rec, origin, 0.0f, WHITE);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
    free_tile_textures();
    cleanup_game();
    return 0;
}
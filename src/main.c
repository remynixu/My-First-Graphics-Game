#include "system/engine.h"
#include "system/chunk.h"
#include "system/entity.h"

int main(void){
    struct engine_ctx engine_ctx = {0};
    struct chunk chunk = {0};
    struct entity player = {0};
    RenderTexture2D game_target = {0};
    Rectangle src_rec = {0}, dest_rec = {0};
    Vector2 origin = {0};
    Camera2D cam = {0};
    if(!ChangeDirectory(GetApplicationDirectory()))
        return -1;
    {
        engine_ctx.screen.height = 600;
        engine_ctx.screen.width = 800;
        engine_ctx.target_fps = 60;
        start_engine(&engine_ctx, "Arundel's Adventure");
        game_target = LoadRenderTexture(engine_ctx.screen.width, engine_ctx.screen.height);
    }
    if(load_tile_textures() != 0)
        return -2;
    if(load_entity_textures() != 0)
        return -3;
    { /* Player set-up */
        player.pos.x = engine_ctx.screen.width / 2;
        player.pos.y = engine_ctx.screen.height / 2;
        player.type = ENTITY_PLAYER;
        player.scale = 2.0f;
    }
    if(parse_chunk("assets/chunks/test.chunk", &chunk) != 0)
        return -4;
    { /* Camera set-up */
        src_rec.width = (float)game_target.texture.width;
        src_rec.height = -(float)game_target.texture.height;
        dest_rec.width = engine_ctx.screen.width;
        dest_rec.height = engine_ctx.screen.height;
        cam.zoom = 1.0f;
    }
    while(!WindowShouldClose()){
        float cam_move;
        update_engine(&engine_ctx);
        cam_move = 400.0f * engine_ctx.delta_time;
        if(engine_ctx.heldkey_flags & KEYCODE_W)
            cam.target.y -= cam_move;
        if(engine_ctx.heldkey_flags & KEYCODE_S)
            cam.target.y += cam_move;
        if(engine_ctx.heldkey_flags & KEYCODE_A)
            cam.target.x -= cam_move;
        if(engine_ctx.heldkey_flags & KEYCODE_D)
            cam.target.x += cam_move;
        BeginTextureMode(game_target);
        {
            ClearBackground(DARKGRAY);
            BeginMode2D(cam);
            {
                draw_chunk(&chunk);
            }
            EndMode2D();
            draw_entity(&player);
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
    end_engine();
    return 0;
}
#include "system/engine.h"
#include "system/screen.h"

#include "system/map/chunk.h"
#include "system/entity/entity.h"

int main(void){
    struct engine_ctx engine_ctx = {0};
    struct chunk chunk = {0};
    struct entity player = {0};
    struct screen screen = {0};
    Camera2D cam = {0};
    if(!ChangeDirectory(GetApplicationDirectory()))
        return -1;
    { /* Engine contexts */
        engine_ctx.screen.height = 600;
        engine_ctx.screen.width = 800;
        engine_ctx.target_fps = 60;
        start_engine(&engine_ctx, "Arundel's Adventure");
    }
    if(load_tile_textures() != 0)
        return -2;
    if(load_entity_textures() != 0)
        return -3;
    { /* Player set-up */
        player.pos.x = engine_ctx.screen.width / 2;
        player.pos.y = engine_ctx.screen.height / 2;
        player.type = ENTITY_PLAYER;
        player.scale = 1.0f;
        player.speed = 100.0f;
    }
    if(parse_chunk("assets/chunks/test.chunk", &chunk) != 0)
        return -4;
    setup_screen(&engine_ctx, &screen);
    { /* Camera set-up */
        cam.offset.x = engine_ctx.screen.width / 2;
        cam.offset.y = engine_ctx.screen.height / 2;
        cam.zoom = 4.0f;
    }
    while(!WindowShouldClose()){
        float player_move;
        update_engine(&engine_ctx);
        player_move = player.speed * engine_ctx.delta_time;
        if(engine_ctx.heldkey_flags & KEYCODE_W)
            player.pos.y -= player_move;
        if(engine_ctx.heldkey_flags & KEYCODE_S)
            player.pos.y += player_move;
        if(engine_ctx.heldkey_flags & KEYCODE_A)
            player.pos.x -= player_move;
        if(engine_ctx.heldkey_flags & KEYCODE_D)
            player.pos.x += player_move;
        cam.target = player.pos;
        BeginTextureMode(screen.target);
        {
            ClearBackground(DARKGRAY);
            BeginMode2D(cam);
            {
                draw_chunk(&chunk);
                draw_entity(&player);
            }
            EndMode2D();
        }
        EndTextureMode();
        BeginDrawing();
        {
            ClearBackground(BLACK); 
            draw_screen(&screen);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
    free_tile_textures();
    end_engine();
    return 0;
}
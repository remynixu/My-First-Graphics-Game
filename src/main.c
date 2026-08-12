#include "system/engine/engine.h"
#include "system/engine/screen.h"
#include "system/entity/entity.h"

#include "system/map/chunk.h"
#include "system/control.h"

#include <stdio.h>

int main(void){
    struct engine_ctx engine_ctx = {0};
    struct chunk chunk = {0};
    struct entity player = {0};
    struct screen screen = {0};
    Camera2D cam = {0};
    if(!ChangeDirectory(GetApplicationDirectory()))
        return -1;
    { /* Engine set-up */
        engine_ctx.screen.height = 600;
        engine_ctx.screen.width = 800;
        engine_ctx.target_fps = 60;
    }
    start_engine(&engine_ctx, "Arundel's Adventure");
    if(load_tile_textures() != 0)
        return -2;
    if(load_entity_textures() != 0)
        return -3;
    setup_entity(engine_ctx.screen.width / 2, engine_ctx.screen.height / 2, ENTITY_PLAYER, &player);
    if(parse_chunk("assets/chunks/test.chunk", &chunk) != 0)
        return -4;
    engine_ctx.curr_chunk = &chunk;
    setup_screen(&engine_ctx, &screen);
    { /* Camera set-up */
        cam.offset.x = engine_ctx.screen.width / 2;
        cam.offset.y = engine_ctx.screen.height / 2;
        cam.zoom = 4.0f;
    }
    while(!WindowShouldClose()){
        update_engine(&engine_ctx);
        control_entity(&engine_ctx, &player);
        cam.target = player.pos;
        BeginTextureMode(screen.target);
        {
            ClearBackground(DARKGRAY);
            BeginMode2D(cam);
            {
                draw_chunk(&chunk);
                draw_entity(&player);
                DrawRectangleLinesEx(get_entity_hitbox(&player), (float)1, RED);
            }
            EndMode2D();
        }
        EndTextureMode();
        BeginDrawing();
        {
            char buf[32] = {0};
            sprintf(buf, "X=%.2f,Y=%.2f", player.pos.x, player.pos.y);
            ClearBackground(BLACK); 
            draw_screen(&screen);
            DrawFPS(10, 10);
            DrawText(buf, 10, 50, 20, DARKGREEN);
        }
        EndDrawing();
    }
    free_entity_textures();
    free_tile_textures();
    end_screen(&screen);
    end_engine();
    return 0;
}
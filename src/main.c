#include "system/map/entity_list.h"
#include "system/map/chunk.h"

#include "system/engine.h"
#include "system/control.h"
#include "system/screen.h"

int main(void){
    struct engine_ctx engine_ctx = {0};
    struct chunk chunk = {0};
    struct entity list[MAX_ENTITY_COUNT] = {0};
    struct screen screen = {0};
    Camera2D cam = {0};
    if(!ChangeDirectory(GetApplicationDirectory()))
        return -1;
    { /* Engine set-up */
        engine_ctx.screen.height = 600;
        engine_ctx.screen.width = 800;
        engine_ctx.target_fps = 60;
    }
    { /* Windows and screen set-up */
        start_engine(&engine_ctx, "A Little Witch's Little Forest");
        setup_screen(&engine_ctx, &screen);
    }
    if(load_tile_textures() != 0)
        return -2;
    if(load_entity_textures() != 0)
        return -3;
    { /* Entity set-up */
        struct entity hint;
        {
            hint.pos.x = engine_ctx.screen.width / 2;
            hint.pos.y = engine_ctx.screen.height / 2;
            hint.type = ENTITY_PLAYER;
        }
        setup_entity(&hint, &list[0]);
        {
            hint.pos.x += 30;
            hint.pos.y += 30;
            hint.type = ENTITY_ROCK;
        }
        setup_entity(&hint, &list[1]);
    }
    if(parse_chunk("assets/data/chunk/test.chunk", &chunk) != 0)
        return -4;
    { /* Game context set-up */
        engine_ctx.game.curr_chunk = &chunk;
        engine_ctx.game.entity_list = list;
    }
    { /* Camera set-up */
        cam.offset.x = engine_ctx.screen.width / 2;
        cam.offset.y = engine_ctx.screen.height / 2;
        cam.zoom = 4.0f;
    }
    while(!WindowShouldClose()){
        {
            update_engine(&engine_ctx);
            control_entity(&engine_ctx, &list[0]);
        }
        cam.target = list[0].pos;
        BeginTextureMode(screen.target);
        {
            ClearBackground(DARKGRAY);
            BeginMode2D(cam);
            {
                draw_chunk(&chunk);
                draw_entities(list);
                draw_entity_hitbox(&list[0]);
                draw_entity_hitbox(&list[1]);
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
    { /* Clean-up */
        free_entity_textures();
        free_tile_textures();
        end_screen(&screen);
        end_engine();
    }
    return 0;
}
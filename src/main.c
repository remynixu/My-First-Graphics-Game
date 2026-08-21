#include "system/engine.h"
#include <raylib.h>

int main(void){
    struct engine_ctx ctx;
    int errcode = 0;
    {
        ctx.screen_height = 600;
        ctx.screen_width = 800;
        ctx.target_fps = 60;
    }
    errcode = engine_init(&ctx);
    if(!errcode)
        engine_perror(errcode);
    for(;ctx.state == ENGINE_STATE_RUNNING; engine_update(&ctx)){
        BeginDrawing();
        {
            ClearBackground(BLACK); 
            DrawFPS(10, 10);
        }
        EndDrawing();
    }
    engine_close();
    return 0;
}

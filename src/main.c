#include "system/engine.h"

#include <string.h>

int main(void){
    struct engine_ctx ctx;
    int errcode = 0;
    {
        struct engine_hint hint;
        {
            hint.window.height = 600;
            hint.window.width = 800;
            hint.target_fps = 60;
        }
        memcpy(&hint.window.title, "Inchoatus", 10);
        errcode = engine_init(&ctx, &hint);
    }
    if(errcode){
        engine_perror();
        return -1;
    }
    while(ctx.state == ENGINE_STATE_RUNNING){
        engine_update(&ctx);
        engine_render(&ctx);
    }
    engine_close(&ctx);
    return 0;
}

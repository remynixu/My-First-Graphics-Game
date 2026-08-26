#include "engine.h"

#include "lib/util.h"

int engine_init(struct engine_ctx *ctx, struct engine_hint *hint){
    UNUSED(ctx);
    UNUSED(hint);
    return 0;
}

void engine_update(struct engine_ctx *ctx){
    UNUSED(ctx);
    return;
}

void engine_render(struct engine_ctx *ctx){
    UNUSED(ctx);
    return;
}

void engine_perror(struct engine_ctx *ctx){
    UNUSED(ctx);
    return;
}

void engine_close(struct engine_ctx *ctx){
    UNUSED(ctx);
    return;
}
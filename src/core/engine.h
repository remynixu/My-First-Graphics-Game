#ifndef ENGINE_H
#define ENGINE_H

#include "lib/byte.h"

enum engine_state{
    ENGINE_STATE_QUIT = 0,
    ENGINE_STATE_RUNNING
};

struct engine_ctx{
    float delta_time;
    enum engine_state state;
};

struct engine_hint{
    byte target_fps;
};

/* Begin the engine, use only once or else :< */
int engine_init(struct engine_ctx *ctx, struct engine_hint *hint);

/* Updates the engine with the recent events. */
void engine_update(struct engine_ctx *ctx);

/* Makes the engine do rendering. */
void engine_render(struct engine_ctx *ctx);

/* If something goes wrong... */
void engine_perror(struct engine_ctx *ctx);

/* Properly closes and cleans up the engine. */
void engine_close(struct engine_ctx *ctx);

#endif /* ENGINE_H */
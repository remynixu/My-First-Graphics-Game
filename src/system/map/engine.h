#ifndef ENGINE_H
#define ENGINE_H

#include <raylib.h>

#include "tile.h"
#include "chunk.h"
#include "entity.h"

enum heldkey_flags{
    KEYCODE_W = (1 << 0),
    KEYCODE_S = (1 << 1),
    KEYCODE_A = (1 << 2),
    KEYCODE_D = (1 << 3),
    KEYCODE_SPC = (1 << 4),
    KEYCODE_Q = (1 << 5),
    KEYCODE_F = (1 << 6),
    KEYCODE_R = (1 << 7)
};

struct engine_ctx{
    int target_fps;
    unsigned char heldkey_flags;
    struct{
        int width;
        int height;
    }screen;
    struct{
        float delta;
        float animation;
    }time;
    struct{
        struct chunk *curr_chunk;
        struct entity *entity_list;
    }game;
};

void start_engine(struct engine_ctx *ctx, const char *title);
void update_engine(struct engine_ctx *ctx);
void end_engine(void);

#endif /* ENGINE_H */
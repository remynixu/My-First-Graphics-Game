#ifndef ENGINE_H
#define ENGINE_H

#include <raylib.h>

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
    struct{
        int width;
        int height;
    }screen;
    int target_fps;
    float delta_time;
    unsigned char heldkey_flags;
    struct chunk *curr_chunk;
};

void start_engine(struct engine_ctx *ctx, const char *title);
void update_engine(struct engine_ctx *ctx);
void end_engine(void);

#endif /* ENGINE_H */
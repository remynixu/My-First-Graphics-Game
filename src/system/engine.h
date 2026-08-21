#ifndef ENGINE_H
#define ENGINE_H

enum engine_state{
    ENGINE_STATE_QUIT = 0,
    ENGINE_STATE_RUNNING
};

struct engine_ctx{
    float delta_time;
    enum engine_state state;
    int target_fps;
    int screen_width;
    int screen_height;
};

int engine_init(struct engine_ctx *hint);
void engine_perror(int errcode);

void engine_update(struct engine_ctx *ctx);
void engine_close(void);

#endif /* ENGINE_H */
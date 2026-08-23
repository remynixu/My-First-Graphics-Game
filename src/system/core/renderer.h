#ifndef RENDERER_H
#define RENDERER_H

#include "primitives/texture.h"
#include "primitives/types.h"

#include "env/env.h"

/*
 * x   = x position in screen pixels.
 * y   = y position in screen pixels.
 * tex = tex
 */
struct renderer_command{
    unsigned int x;
    unsigned int y;
    struct texture *tex;
};

#define MAX_RENDERER_COMMAND    1024

struct renderer_buffer{
    struct renderer_command pool[MAX_RENDERER_COMMAND];
    unsigned int count;
};

int renderer_init(struct screen_info *scr);

void renderer_clean(struct renderer_buffer *buf);
void renderer_push(struct renderer_buffer *buf, struct renderer_command *cmd);
void renderer_flush(struct renderer_buffer *buf, struct screen_info *scr);

void renderer_quit(void);

#endif /* RENDERER_H */
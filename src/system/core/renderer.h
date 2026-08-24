#ifndef RENDERER_H
#define RENDERER_H

#include "primitives/texture.h"
#include "primitives/types.h"

/* Backwards-compatibility? Will remove soon :< */
typedef struct texture renderer_command;

#define MAX_RENDERER_COMMAND    1024

struct renderer_buffer{
    renderer_command pool[MAX_RENDERER_COMMAND];
    unsigned int count;
};

void renderer_clean(struct renderer_buffer *buf);
void renderer_push(struct renderer_buffer *buf, renderer_command *cmd);
void renderer_flush(struct renderer_buffer *buf);

#endif /* RENDERER_H */
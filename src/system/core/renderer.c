#include "renderer.h"

#include "env/window.h"

#include <string.h>

void renderer_clean(struct renderer_buffer *buf){
    memset(buf, 0, sizeof(*buf));
}

void renderer_push(struct renderer_buffer *buf, renderer_command *cmd){
    buf->pool[buf->count] = *cmd;
    buf->count++;
}

static void _sort(struct renderer_buffer *buf){
    unsigned int i;
    int j;
    renderer_command target;
    renderer_command *r = buf->pool;
    for(i = 1; i < buf->count; i++){
        target = r[i];
        for(j = i - 1; j > -1 && r[j].mod.dst.y > target.mod.dst.y; j--)
            r[j + 1] = r[j];
        r[j + 1] = target;
    }
}

static void _render(renderer_command *cmd){
    tex_draw(cmd);
}

void renderer_flush(struct renderer_buffer *buf){
    unsigned int i = 0;
    _sort(buf);
    for(i = 0; i < buf->count; i++)
        _render(&buf->pool[i]);
    renderer_clean(buf);
}
#include "renderer.h"

#include "env/env.h"
#include "env/window.h"

#include <raylib.h>
#include <string.h>

static RenderTexture2D screen = {0};

int renderer_init(struct screen_info *scr){
    if(window_init(scr))
        return -1;
    screen = LoadRenderTexture(scr->width, scr->height);
    return 0;
}

void renderer_clean(struct renderer_buffer *buf){
    memset(buf, 0, sizeof(*buf));
}

void renderer_push(struct renderer_buffer *buf, renderer_command *cmd){
    buf->pool[buf->count] = *cmd;
    buf->count++;
}

static void _sort(struct renderer_buffer *buf){
    int i;
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

void renderer_flush(struct renderer_buffer *buf, struct screen_info *scr){
    _sort(buf);
    BeginTextureMode(screen);
    {
        int i;
        ClearBackground(GRAY);
        for(i = 0; i < buf->count; i++)
            _render(&buf->pool[i]);
    }
    EndTextureMode();
    BeginDrawing();
    {
        Rectangle src = {0};
        Rectangle dst = {0};
        Vector2 org = {0};
        {
            src.height = dst.height = -screen.texture.height;   /* Or else screen will be upside-down... */
            src.width = dst.width = screen.texture.width;
        }
        DrawTexturePro(screen.texture, src, dst, org, 0.0f, WHITE);
    }
    EndDrawing();
    renderer_clean(buf);
}

void renderer_quit(void){
    window_quit();
    UnloadRenderTexture(screen);
}
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

void renderer_push(struct renderer_buffer *buf, struct renderer_command *cmd){
    buf->pool[buf->count++] = *cmd;
}

static void _sort(struct renderer_buffer *buf){
    int i;
    int j;
    struct renderer_command target;
    struct renderer_command *r = buf->pool;
    for(i = 1; i < buf->count; i++){
        target = r[i];
        for(j = i - 1; j > -1 && r[j].y > target.y; j--)
            r[j + 1] = r[j];
        r[j + 1] = target;
    }
}

static void _render(struct renderer_command *cmd){
    tex_draw(cmd->tex);
}

static void _clean(struct renderer_buffer *buf){
    memset(buf, 0, buf->count * sizeof(*buf->pool));
}

void renderer_flush(struct renderer_buffer *buf, struct screen_info *scr){
    _sort(buf);
    BeginTextureMode(screen);
    {
        int i;
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
            src.height = dst.height = screen.texture.height;
            src.width = dst.width = screen.texture.width;
        }
        ClearBackground(GRAY);
        DrawTexturePro(screen.texture, src, dst, org, 0.0f, WHITE);
    }
    EndDrawing();
    _clean(buf);
}

void renderer_quit(void){
    window_quit();
    UnloadRenderTexture(screen);
}
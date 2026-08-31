#include "md_video.h"

#include <raylib.h>

#define MD_SCREEN_WIDTH     800
#define MD_SCREEN_HEIGHT    600

DATA struct{
    RenderTexture2D sized;
    Texture2D initial;
}md_screen;

int md_video_init(struct mi_video_ram *mi_vram){
    {
        InitWindow(MD_SCREEN_WIDTH, MD_SCREEN_HEIGHT, " ");
        SetTargetFPS(60);
    }
    md_screen.sized = LoadRenderTexture(MI_PIXEL_BUFFER_WIDTH, MI_PIXEL_BUFFER_HEIGHT);
    if(!IsRenderTextureValid(md_screen.sized))
        return -1;
    {
        Image _hint;
        {
            _hint.data = mi_vram->buffer;
            _hint.width = MI_PIXEL_BUFFER_WIDTH;
            _hint.height = MI_PIXEL_BUFFER_HEIGHT;
            _hint.mipmaps = 1;
            _hint.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
        }
        md_screen.initial = LoadTextureFromImage(_hint);
    }
    if(!IsTextureValid(md_screen.initial)){
        UnloadRenderTexture(md_screen.sized);
        return -2;
    }
    return 0;
}

#define MD_MSG_MAX_STRLEN   32

RODATA char md_msg[][MD_MSG_MAX_STRLEN] = {
    "[MD_VIDEO]:\'SUCCESS\'",
    "[MD_VIDEO]:\'FRAMEBUFFER ERROR\'",
    "[MD_VIDEO]:\'TEXTURE ERROR\'"
};

const char *md_video_strerror(int errcode){
    return md_msg[-errcode];
}

void md_video_clear(struct mi_video_ram *mi_vram){
    int i;
    char _null_pixel[MI_PIXEL_BYTE_SIZE];
    {
        _null_pixel[0] = 30;
        _null_pixel[1] = 30;
        _null_pixel[2] = 30;
        _null_pixel[3] = 255;
    }
    for(i = 0; i < MI_PIXEL_BUFFER_WIDTH * MI_PIXEL_BUFFER_HEIGHT; i++)
        mi_pixel_copy(mi_vram->buffer + i * MI_PIXEL_BYTE_SIZE, _null_pixel);
}

RODATA struct{
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
}video_size = {
    {
        0,
        0,
        MI_PIXEL_BUFFER_WIDTH,
        MI_PIXEL_BUFFER_HEIGHT
    },
    {
        0,
        0,
        MD_SCREEN_WIDTH,
        MD_SCREEN_HEIGHT
    },
    {
        0,
        0
    }
};

void md_video_from_vram(struct mi_video_ram *mi_vram){
    int x, y;
    md_video_clear(mi_vram);
    UpdateTexture(md_screen.initial, mi_vram);
    BeginTextureMode(md_screen.sized);
    {
        DrawTexture(md_screen.initial, 0, 0, WHITE);
    }
    EndTextureMode();
    BeginDrawing();
    {
        DrawTexturePro(md_screen.sized.texture, video_size.source, video_size.dest, video_size.origin, 0.0f, WHITE);
    }
    EndDrawing();
}
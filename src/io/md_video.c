#include "md_video.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The code below is expected to be different for different platforms.
 */

#define MD_SCREEN_WIDTH     800
#define MD_SCREEN_HEIGHT    600

#include <raylib.h>

DATA struct{
    RenderTexture2D sized;
    Texture2D initial;
}md_screen;

int md_video_init(struct md_video_ram *md_vram){
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
            _hint.data = md_vram->buffer;
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

void md_video_clear(struct md_video_ram *md_vram){
    int i;
    char _null_pixel[MD_PIXEL_BYTE_SIZE];
    struct pixel_config pxl_hint;
    {
        pxl_hint.r = 30;
        pxl_hint.g = 30;
        pxl_hint.b = 30;
        pxl_hint.a = 255;
    }
    md_pixel_set(_null_pixel, pxl_hint);
    for(i = 0; i < MD_VIDEO_RAM_BUFFER_SIZE; i += MD_PIXEL_BYTE_SIZE)
        md_pixel_copy(md_vram->buffer + i, _null_pixel);
}

RODATA struct{
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
}md_video_size = {
    {   /* our framebuffer's size */
        0,
        0,
        MI_PIXEL_BUFFER_WIDTH,
        MI_PIXEL_BUFFER_HEIGHT
    },
    {   /* the platform's framebuffer size */
        0,
        0,
        MD_SCREEN_WIDTH,
        MD_SCREEN_HEIGHT
    },
    {   /* we have offsets apparently... ._. */
        0,
        0
    }
};

void md_video_from_vram(struct md_video_ram *md_vram){
    int x, y;
    md_video_clear(md_vram);
    UpdateTexture(md_screen.initial, md_vram);
    BeginTextureMode(md_screen.sized);
    {
        DrawTexture(md_screen.initial, 0, 0, WHITE);
    }
    EndTextureMode();
    BeginDrawing();
    {
        DrawTexturePro(
            md_screen.sized.texture,
            md_video_size.source,
            md_video_size.dest,
            md_video_size.origin,
            0.0f,
            WHITE
        );
    }
    EndDrawing();
}

void md_video_quit(struct md_video_ram *md_vram){
    UNUSED md_vram;
    UnloadTexture(md_screen.initial);
    UnloadRenderTexture(md_screen.sized);
}
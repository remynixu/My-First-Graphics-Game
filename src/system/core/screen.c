#define _TYPES_CONVERTIONS
#include "primitives/types.h"

#define _TEXTURE_CONVERTIONS
#include "primitives/texture.h"

#include "screen.h"

#include <raylib.h>

static struct screen_info _rt2d_to_scrinfo(RenderTexture2D rt2d){
    struct screen_info scrinfo = {0};
    {
        impltex_to_texinfo(rt2d.texture, scrinfo.texinfo);
        impltex_to_texinfo(rt2d.depth, scrinfo.depth);
        scrinfo.id = rt2d.id;
    }
    return scrinfo;
}

void screen_make(struct screen *scr, struct vector2 size){
    scr->info = _rt2d_to_scrinfo(LoadRenderTexture(size.x, size.y));
    {
        scr->pos.dst.width = size.x;
        scr->pos.dst.height = size.y;
        scr->pos.dst.x = scr->pos.dst.y = 0;
    }
    {
        scr->pos.src.width = scr->info.texinfo.width;
        scr->pos.src.height = scr->info.texinfo.height;
        scr->pos.src.x = scr->pos.src.y = 0;
    }
    {
        scr->pos.org.x = 0;
        scr->pos.org.y = 0;
    }
}

int screen_init(struct screen *scr, struct window_info *info){
    if(window_init(info))
        return -1;
    screen_make(scr, tovec2(info->width, info->height));
    return 0;
}

static RenderTexture2D _scrinfo_to_rt2d(struct screen_info scrinfo){
    RenderTexture2D rt2d = {0};
    {
        impltex_to_texinfo(scrinfo.texinfo, rt2d.texture);
        impltex_to_texinfo(scrinfo.depth, rt2d.depth);
        rt2d.id = scrinfo.id;
    }
    return rt2d;
}

void screenmode_begin(struct screen *scr){
    BeginTextureMode(_scrinfo_to_rt2d(scr->info));
    ClearBackground(BLACK);
}

void screenmode_end(void){
    EndTextureMode();
}

void screen_update(struct screen *scr){
    BeginDrawing();
    {
        Texture2D t2d = {0};
        Rectangle rec[2] = {0};
        Vector2 org = {0};
        {
            impltex_to_texinfo(scr->info.texinfo, t2d);
            implrec_to_rec(scr->pos.src, rec[0]);
            implrec_to_rec(scr->pos.dst, rec[1]);
            implvec2_to_vec2(scr->pos.org, org);
        }
        rec[0].height = -rec[0].height;
        DrawTexturePro(t2d, rec[0], rec[1], org, 0.0f, WHITE);
    }
    EndDrawing();
}

void screen_quit(struct screen *scr){
    UnloadRenderTexture(_scrinfo_to_rt2d(scr->info));
}
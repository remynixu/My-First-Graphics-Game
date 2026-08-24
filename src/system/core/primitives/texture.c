#define _TYPES_CONVERTIONS
#include "types.h"

#define _TEXTURE_CONVERTIONS
#include "texture.h"

#include <raylib.h>

static struct texture_info _t2d_to_texinfo(Texture2D t2d){
    struct texture_info texinfo;
    impltex_to_texinfo(t2d, texinfo);
    return texinfo;
}

int texinfo_load(struct texture_info *info, const char *image_path){
    Texture2D t2d = LoadTexture(image_path);
    if(!IsTextureValid(t2d)){
        UnloadTexture(t2d);
        return -1;
    }
    *info = _t2d_to_texinfo(t2d);
    return 0;
}

static Texture2D _tot2d(struct texture_info texinfo){
    Texture2D t2d;
    impltex_to_texinfo(texinfo, t2d);
    return t2d;
}

static Rectangle _torec(struct rectangle r){
    Rectangle rec;
    implrec_to_rec(r, rec);
    return rec;
}

static Vector2 _tovec2(int x, int y){
    Vector2 vec2;
    {
        vec2.x = x;
        vec2.y = y;
    }
    return vec2;
}

void tex_draw(struct texture *tex){
    DrawTexturePro(_tot2d(tex->info), _torec(tex->mod.src),
        _torec(tex->mod.dst), _tovec2(tex->mod.org.x, tex->mod.org.y), 0.0f, WHITE);
}

void texinfo_unload(struct texture_info *info){
    UnloadTexture(_tot2d(*info));
}
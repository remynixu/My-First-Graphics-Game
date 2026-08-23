#include "texture.h"

#include <raylib.h>

static struct texture_info _t2d_to_texinfo(Texture2D t2d){
    struct texture_info tex;
    {
        tex.id = t2d.id;
        tex.width = t2d.width;
        tex.height = t2d.height;
        tex.mipmaps = t2d.mipmaps;
        tex.format = t2d.format;
    }
    return tex;
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

static Texture2D _tot2d(struct texture_info info){
    Texture2D t2d;
    {
        t2d.id = info.id;
        t2d.width = info.width;
        t2d.height = info.height;
        t2d.mipmaps = info.mipmaps;
        t2d.format = info.format;
    }
    return t2d;
}

static Rectangle _torec(struct rectangle r){
    Rectangle rec;
    {
        rec.height = r.height;
        rec.width = r.width;
        rec.x = r.x;
        rec.y = r.y;
    }
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
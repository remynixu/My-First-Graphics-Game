#include "texture.h"

#include <raylib.h>

static struct texture _t2dtotex(Texture2D t2d){
    struct texture tex;
    {
        tex.id = t2d.id;
        tex.width = t2d.width;
        tex.height = t2d.height;
        tex.mipmaps = t2d.mipmaps;
        tex.format = t2d.format;
    }
    return tex;
}

int tex_load(struct texture *tex, const char *image_path){
    Texture2D t2d = LoadTexture(image_path);
    if(!IsTextureValid(t2d)){
        UnloadTexture(t2d);
        return -1;
    }
    *tex = _t2dtotex(t2d);
    return 0;
}

static Texture2D _tot2d(struct texture tex){
    Texture2D t2d;
    {
        t2d.id = tex.id;
        t2d.width = tex.width;
        t2d.height = tex.height;
        t2d.mipmaps = tex.mipmaps;
        t2d.format = tex.format;
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

void tex_draw(struct texture *tex, struct texture_modifier *mod){
    DrawTexturePro(_tot2d(*tex), _torec(mod->src), _torec(mod->dst), _tovec2(mod->org.x, mod->org.y), 0.0f, WHITE);
}

void tex_unload(struct texture *tex){
    UnloadTexture(_tot2d(*tex));
}
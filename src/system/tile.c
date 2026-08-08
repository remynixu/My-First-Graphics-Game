#include "tile.h"

static const char tex_pathlist[][32] = {
    "assets/null_texture.png",
    "assets/lol.png"
};

int load_tile(struct tile *t){
    t->tex = LoadTexture(tex_pathlist[t->type]);
    if(t->tex.width != 32 || t->tex.height != 32){
        UnloadTexture(t->tex);
        t->tex = LoadTexture(tex_pathlist[0]);
        if(!IsTextureValid(t->tex))
            return -2;
        return -1;
    }
    return 0;
}

void draw_tile(struct tile *t){
    Vector2 origin;
    Rectangle src, dst;
    origin.x = 16.0f;
    origin.y = 16.0f;
    src.x = src.y = 0.0f;
    src.height = dst.height = 32.0f;
    src.width = dst.width = 32.0f;
    dst.x = (float)t->x;
    dst.y = (float)t->y;
    DrawTexturePro(t->tex, src, dst, origin, 0.0f, WHITE);
}

void free_tile(struct tile *t){
    UnloadTexture(t->tex);
}
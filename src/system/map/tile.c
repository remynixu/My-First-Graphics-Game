#include "tile.h"

Rectangle get_tile_hitbox(const struct tile *const t){
    Rectangle hb;
    hb.height = (float)TILE_PIXEL_HEIGHT;
    hb.width = (float)TILE_PIXEL_WIDTH;
    hb.x = (float)t->x;
    hb.y = (float)t->y;
    return hb;
}

static const char tex_pathlist[MAX_TILE_TYPE][64] = {
    "assets/textures/tile/null.png",
    "assets/textures/tile/stone.png",
    "assets/textures/tile/placeholder.png"
};

static Texture2D tex_list[MAX_TILE_TYPE] = {0};

static int _load_tex(const int i){
    tex_list[i] = LoadTexture(tex_pathlist[i]);
    if(!IsTextureValid(tex_list[i])){
        UnloadTexture(tex_list[i]);
        return -1;
    }
    SetTextureFilter(tex_list[i], TEXTURE_FILTER_POINT);
    return 0;
}

int load_tile_textures(void){
    int i;
    int errcode;
    for(i = 0; i < MAX_TILE_TYPE; i++){
        errcode =_load_tex(i);
        if(errcode == -1)
            return -(i + 1);
    }
    return 0;
}

void draw_tile(const struct tile *const t){
    Vector2 origin = {0};
    Rectangle src, dst;
    src.x = src.y = 0.0f;
    src.height = dst.height = (float)TILE_PIXEL_HEIGHT;
    src.width = dst.width = (float)TILE_PIXEL_WIDTH;
    dst.x = (float)t->x;
    dst.y = (float)t->y;
    DrawTexturePro(tex_list[t->type], src, dst, origin, 0.0f, WHITE);
}

static void _free_tile(const int i){
    UnloadTexture(tex_list[i]);
}

void free_tile_textures(void){
    int i = 0;
    for(i = 0; i < MAX_TILE_TYPE; i++)
        _free_tile(i);
}
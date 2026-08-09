#include "tile.h"

static const char tex_pathlist[MAX_TILE_TYPE][32] = {
    "assets/textures/null.png",
    "assets/textures/ground.png"
};

static Texture2D tex_list[MAX_TILE_TYPE] = {0};

static int _load_tex(int i){
    tex_list[i] = LoadTexture(tex_pathlist[i]);
    if(tex_list[i].width != TILE_PIXEL_WIDTH || tex_list[i].height != TILE_PIXEL_HEIGHT){
        UnloadTexture(tex_list[i]);
        tex_list[i] = LoadTexture(tex_pathlist[0]);
        if(!IsTextureValid(tex_list[i]))
            return -2;
        return -1;
    }
    return 0;
}

int load_tile_textures(void){
    int i;
    for(i = 0; i < MAX_TILE_TYPE; i++){
        if(_load_tex(i) != 0)
            return -1;
    }
    return 0;
}

void draw_tile(struct tile *t){
    Vector2 origin;
    Rectangle src, dst;
    origin.x = (float)TILE_PIXEL_WIDTH / 2;
    origin.y = (float)TILE_PIXEL_HEIGHT / 2;
    src.x = src.y = 0.0f;
    src.height = dst.height = (float)TILE_PIXEL_HEIGHT;
    src.width = dst.width = (float)TILE_PIXEL_WIDTH;
    dst.x = (float)t->x;
    dst.y = (float)t->y;
    DrawTexturePro(tex_list[t->type], src, dst, origin, 0.0f, WHITE);
}

static void _free_tile(int i){
    UnloadTexture(tex_list[i]);
}

void free_tile_textures(void){
    int i = 0;
    for(i = 0; i < MAX_TILE_TYPE; i++)
        _free_tile(i);
}
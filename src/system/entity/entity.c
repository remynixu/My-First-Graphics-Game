#include "entity.h"

static const char tex_pathlist[MAX_ENTITY_TYPE][32] = {
    "assets/textures/null_entity.png",
    "assets/textures/arundel.png"
};

static Texture2D tex_list[MAX_ENTITY_TYPE] = {0};

static int _load_tex(int i){
    tex_list[i] = LoadTexture(tex_pathlist[i]);
    if(!IsTextureValid(tex_list[i])){
        UnloadTexture(tex_list[i]);
        tex_list[i] = LoadTexture(tex_pathlist[0]);
        if(!IsTextureValid(tex_list[i]))
            return -2;
        return -1;
    }
    return 0;
}

int load_entity_textures(void){
    int i;
    for(i = 0; i < MAX_ENTITY_TYPE; i++){
        if(_load_tex(i) != 0)
            return -1;
    }
    return 0;
}

void draw_entity(struct entity *e){
    Vector2 origin;
    Rectangle src, dst;
    float width = (float)tex_list[e->type].width;
    float height = (float)tex_list[e->type].height;
    {
        origin.x = (width * e->scale) / 2;
        origin.y = (height * e->scale) / 2;
    }
    {
        src.x = src.y = 0.0f;
        src.height = height;
        src.width = width;
    }
    {
        dst.x = e->pos.x;
        dst.y = e->pos.y;
        dst.height = height * e->scale;
        dst.width = width * e->scale;
    }
    DrawTexturePro(tex_list[e->type], src, dst, origin, 0.0f, WHITE);
}

static void _free_tile(int i){
    UnloadTexture(tex_list[i]);
}

void free_entity_textures(void){
    int i = 0;
    for(i = 0; i < MAX_ENTITY_TYPE; i++)
        _free_tile(i);
}
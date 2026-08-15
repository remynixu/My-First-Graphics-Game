#include "entity.h"

const static struct{
    const char filepath[32];
    float scale;
    float speed;
    struct{
        float x;    /* +1 = left    */
        float y;    /* +1 = up      */
    }hitbox_offset;
    struct{
        float width;    /* +1 = right   */
        float height;   /* +1 = down    */
    }hitbox_sizemod;
}_metadata_list[MAX_ENTITY_TYPE] = {
    {
        "assets/textures/null_entity.png",
        (float)1,
        (float)100,
        {0},
        {0}
    },
    {
        "assets/textures/arundel.png",
        (float)1,
        (float)50,
        {
            (float)-7.5f,
            (float)-7
        },
        {
            (float)-14,
            (float)-8
        }
    }
};

static Texture2D _tex_arr[MAX_ENTITY_TYPE] = {0};

Rectangle get_entity_hitbox(struct entity *e){
    Rectangle hb;
    int i = e->type;
    float width = _tex_arr[i].width * _metadata_list[i].scale;
    float height = _tex_arr[i].height * _metadata_list[i].scale;
    float org_x = width / 2;
    float org_y = height / 2;
    {
        hb.x = e->pos.x - org_x;
        hb.y = e->pos.y - org_y;
        hb.height = height;
        hb.width = width;
    }
    {
        hb.x -= _metadata_list[i].hitbox_offset.x;
        hb.y -= _metadata_list[i].hitbox_offset.y;
        hb.width += _metadata_list[i].hitbox_sizemod.width;
        hb.height += _metadata_list[i].hitbox_sizemod.height;
    }
    return hb;
}

static int _load_tex(int i){
    _tex_arr[i] = LoadTexture(_metadata_list[i].filepath);
    if(!IsTextureValid(_tex_arr[i])){
        UnloadTexture(_tex_arr[i]);
        _tex_arr[i] = LoadTexture(_metadata_list[0].filepath);
        if(!IsTextureValid(_tex_arr[i]))
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

void setup_entity(int x, int y, enum entity_type type, struct entity *e){
        e->pos.x = (float)x;
        e->pos.y = (float)y;
        e->type = type;
        e->speed = _metadata_list[type].speed;
}

void draw_entity(struct entity *e){
    Vector2 origin = {0};
    Rectangle src, dst;
    int i = e->type;
    float width = _tex_arr[i].width;
    float height = _tex_arr[i].height;
    {
        origin.x = (width * _metadata_list[i].scale) / 2;
        origin.y = (height * _metadata_list[i].scale) / 2;
    }
    {
        src.x = src.y = 0.0f;
        src.height = height;
        src.width = width;
    }
    {
        dst.x = e->pos.x;
        dst.y = e->pos.y;
        dst.height = height * _metadata_list[i].scale;
        dst.width = width * _metadata_list[i].scale;
    }
    DrawTexturePro(_tex_arr[i], src, dst, origin, 0.0f, WHITE);
}

static void _free_tile(int i){
    UnloadTexture(_tex_arr[i]);
}

void free_entity_textures(void){
    int i = 0;
    for(i = 0; i < MAX_ENTITY_TYPE; i++)
        _free_tile(i);
}

static void _sort(struct entity *e){
    int i;
    int j;
    struct entity target;
    for(i = 1; i < MAX_ENTITY_COUNT; i++){
        target = e[i];
        for(j = i - 1; j > -1 && e[i].pos.y > target.pos.y; j--)
            e[j + 1] = e[j];
        e[j + 1] = target;
    }
}

void draw_entities(struct entity *list){
    int i;
    _sort(list);
    for(i = 0; i < MAX_ENTITY_COUNT; i++)
        draw_entity(&list[i]);
}
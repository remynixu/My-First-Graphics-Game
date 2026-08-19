#include "entity.h"
#include "entity_metadata.h"

static Texture2D _tex_arr[MAX_ENTITY_TYPE] = {0};

Rectangle get_entity_hitbox(const struct entity *const e){
    Rectangle hb;
    int i = e->type;
    float width = _tex_arr[i].width * _metadata_list[i].scale;
    float height = _tex_arr[i].height * _metadata_list[i].scale;
    if(i == ENTITY_PLAYER)
        width /= 4;
    {
        float org_x = width / 2;
        float org_y = height / 2;
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

void draw_entity_hitbox(const struct entity *const e){
    DrawRectangleLinesEx(get_entity_hitbox(e), ENTITY_HITBOX_THICKNESS, ENTITY_HITBOX_COLOR);
}

static int _load_tex(const int i){
    _tex_arr[i] = LoadTexture(_metadata_list[i].filepath);
    if(!IsTextureValid(_tex_arr[i])){
        UnloadTexture(_tex_arr[i]);
        return -1;
    }
    SetTextureFilter(_tex_arr[i], TEXTURE_FILTER_POINT);
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

void setup_entity(const struct entity *const hint, struct entity *const e){
        e->pos.x = (float)hint->pos.x;
        e->pos.y = (float)hint->pos.y;
        e->type = hint->type;
        e->speed = _metadata_list[hint->type].speed;
}

void draw_entity(const struct entity *const e){
    Vector2 origin = {0};
    Rectangle src, dst;
    int i = e->type;
    float width = _tex_arr[i].width;
    float height = _tex_arr[i].height;
    if(i == ENTITY_PLAYER)
        width /= 4;     /* Because it's a spritesheet. */
    {
        origin.x = (width * _metadata_list[i].scale) / 2;
        origin.y = (height * _metadata_list[i].scale) / 2;
    }
    {
        src.x = src.y = 0.0f;
        src.height = height;
        src.width = width;
    }
    switch(e->direction){
        case ENTITY_UP:{
            src.x += width;
            break;
        }
        case ENTITY_LEFT:{
            src.x += width * 2;
            break;
        }
        case ENTITY_RIGHT:{
            src.x += width * 3;
            break;
        }
        case ENTITY_DOWN:
        default:
        break;
    }
    {
        dst.x = e->pos.x;
        dst.y = e->pos.y;
        dst.height = height * _metadata_list[i].scale;
        dst.width = width * _metadata_list[i].scale;
    }
    DrawTexturePro(_tex_arr[i], src, dst, origin, 0.0f, WHITE);
}

static void _free_ent(const int i){
    UnloadTexture(_tex_arr[i]);
}

void free_entity_textures(void){
    int i = 0;
    for(i = 0; i < MAX_ENTITY_TYPE; i++)
        _free_ent(i);
}
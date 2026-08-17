#include "entity.h"
#include "entity_metadata.h"

static Texture2D _tex_arr[MAX_ENTITY_TYPE] = {0};

Rectangle get_entity_hitbox(const struct entity *const e){
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

void setup_entity(const int x, const int y, const enum entity_type type, struct entity *const e){
        e->pos.x = (float)x;
        e->pos.y = (float)y;
        e->type = type;
        e->speed = _metadata_list[type].speed;
}

void draw_entity(const struct entity *const e){
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

static void _free_tile(const int i){
    UnloadTexture(_tex_arr[i]);
}

void free_entity_textures(void){
    int i = 0;
    for(i = 0; i < MAX_ENTITY_TYPE; i++)
        _free_tile(i);
}

static void _sort(struct entity *const e){
    int i;
    int j;
    struct entity target;
    for(i = 1; i < MAX_ENTITY_COUNT; i++){
        target = e[i];
        for(j = i - 1; j > -1 && e[j].pos.y > target.pos.y; j--)
            e[j + 1] = e[j];
        e[j + 1] = target;
    }
}

#include <string.h>

void draw_entities(const struct entity *const list){
    int i;
    struct entity el[MAX_ENTITY_COUNT];
    memcpy(el, list, sizeof(*el) * MAX_ENTITY_COUNT);
    _sort(el);
    for(i = 0; i < MAX_ENTITY_COUNT; i++){
        if(el[i].type == ENTITY_NULL)
            continue;
        draw_entity(&el[i]);
    }
}

#include <stdio.h>
#include "chunk.h"

int parse_spawntable(const char *filename, struct entity *const list){
    FILE *f = fopen(filename, "r");
    char magic[12] = {0};
    int r, c;
    if(!f)
        return -1; /* file may not exist */
    if(fscanf(f, "%11s", magic) != 1){
        fclose(f);
        return -2; /* unreadable header */
    }
    if(strcmp(magic, "SPAWNTABLE") != 0){
        return -3; /* invalid header */
    }
    for(c = 0; c < MAX_CHUNK_HEIGHT; c++){
        for(r = 0; r < MAX_CHUNK_WIDTH; r++){
            int i = (c * MAX_CHUNK_WIDTH) + r;
            if(fscanf(f, "%u", &list[i].type) != 1){
                fclose(f);
                return -4; /* incomplete/corrupt/invalid data */
            }
            list[i].pos.x = r * TILE_PIXEL_WIDTH;
            list[i].pos.y = c * TILE_PIXEL_HEIGHT;
            if(r < MAX_CHUNK_WIDTH - 1){
                if(fgetc(f) != ':'){
                    fclose(f);
                    return -5; /* missing colon separator */
                }
            }
        }
        fgetc(f); /* skip trailing newline */
    }
    return 0;
}
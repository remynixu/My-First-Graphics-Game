#include "map.h"

Vector2 ftov(float x, float y){
    Vector2 v2;
    v2.x = x;
    v2.y = y;
    return v2;
}

#include <stdio.h>

int init_map(struct map *m, Vector2 size, Vector2 cam_pos, const char *png_path, float tex_scale){
    FILE *f = fopen(png_path, "rb");
    if(!f){
        printf("MAP_ERROR:");
        perror(png_path);
        return -1;
    }
    m->camera = cam_pos;
    m->dimensions = size;
    m->texture = LoadTexture(png_path);
    SetTextureFilter(m->texture, TEXTURE_FILTER_POINT);
    m->tex_scale = tex_scale;
    return 0;
}

void draw_map(struct map *m){
    Vector2 pos;
    pos.x = m->dimensions.x - m->camera.x;
    pos.y = m->dimensions.y - m->camera.y;
    DrawTextureEx(m->texture, pos, 0, m->tex_scale, WHITE);
}

#include <string.h>

void cleanup_map(struct map *m){
    UnloadTexture(m->texture);
    memset(m, 0, sizeof(*m));
}
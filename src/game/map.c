#include "map.h"

Vector2 ftov(float x, float y){
    Vector2 v2;
    v2.x = x;
    v2.y = y;
    return v2;
}

#include <stdio.h>

int init_map(struct map *m, Vector2 size, struct map_cam cam, const char *png_path, struct map_tex tex){
    FILE *f = fopen(png_path, "rb");
    if(!f){
        printf("MAP_ERROR:");
        perror(png_path);
        return -1;
    }
    m->cam = cam;
    m->dimensions = size;
    m->tex.texture = LoadTexture(png_path);
    SetTextureFilter(m->tex.texture, TEXTURE_FILTER_POINT);
    m->tex.tex_scale = tex.tex_scale;
    return 0;
}

void draw_map(struct map *m){
    Vector2 pos;
    pos.x = m->dimensions.x - m->cam.pos.x;
    pos.y = m->dimensions.y - m->cam.pos.y;
    DrawTextureEx(m->tex.texture, pos, 0, (float)m->tex.tex_scale, WHITE);
}

#include <string.h>

void cleanup_map(struct map *m){
    UnloadTexture(m->tex.texture);
    memset(m, 0, sizeof(*m));
}
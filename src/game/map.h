#ifndef MAP_H
#define MAP_H

#include "game.h"

struct map{
    Vector2 dimensions;
    Vector2 camera;
    Texture2D texture;
    float tex_scale;
};

Vector2 ftov(float x, float y);

int init_map(struct map *m, Vector2 size, Vector2 cam_pos, const char *png_path, float tex_scale);

void draw_map(struct map *m);
void cleanup_map(struct map *m);

#endif /* MAP_H */
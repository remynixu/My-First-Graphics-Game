#ifndef MAP_H
#define MAP_H

#include "game.h"

struct map_cam{
    Vector2 pos;
    int speed;
};

struct map_tex{
    Texture2D texture;
    int tex_scale;
};

struct map{
    Vector2 dimensions;
    struct map_cam cam;
    struct map_tex tex;
};

Vector2 ftov(float x, float y);

int init_map(struct map *m, Vector2 size, struct map_cam cam, const char *png_path, struct map_tex tex);

void draw_map(struct map *m);
void cleanup_map(struct map *m);

#endif /* MAP_H */
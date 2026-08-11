#ifndef TILE_H
#define TILE_H

#include <raylib.h>

enum tile_type{
    TILE_NULL   = 0,
    TILE_STONE_WALL,
    MAX_TILE_TYPE
};

#define TILE_PIXEL_WIDTH    16
#define TILE_PIXEL_HEIGHT   16

struct tile{
    enum tile_type type;
    int x;
    int y;
};

Rectangle get_tile_hitbox(struct tile *t);

int load_tile_textures(void);
void draw_tile(struct tile *t);
void free_tile_textures(void);

#endif /* TILE_H */
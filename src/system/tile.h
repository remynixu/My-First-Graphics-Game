#ifndef TILE_H
#define TILE_H

#include "game.h"

enum tile_type{
    TILE_NULL   = 0,
    TILE_GROUND,
    /* Future tiles here. */
    MAX_TILE_TYPE
};

#define TILE_PIXEL_WIDTH    32
#define TILE_PIXEL_HEIGHT   32

/*
 * A tile makes up a chunk of a map, it has a type and two integers about its
 * screen position.
 */
struct tile{
    enum tile_type type;
    int x;
    int y;
};

/*
 * Load the textures to be used by the library, currently an array of 32x32px
 * PNGs.
 */
int load_tile_textures(void);

/*
 * Draw a tile to the screen.
 */
void draw_tile(struct tile *t);

/*
 * Free the textures used by the library.
 */
void free_tile_textures(void);

#endif /* TILE_H */
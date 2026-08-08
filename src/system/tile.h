#ifndef TILE_H
#define TILE_H

#include "game.h"

enum tile_type{
    TILE_NULL   = 0
    /* Future tiles here. */
};

/*
 * A tile makes up a chunk of a map, it has a type and two integers about its
 * screen position.
 */
struct tile{
    Texture2D tex;
    /* Only these must be initialized manually: */
    enum tile_type type;
    int x;
    int y;
};

/*
 * Load a tile to memory.
 */
int load_tile(struct tile *t);

/*
 * Draw a tile to the screen.
 */
void draw_tile(struct tile *t);

/*
 * Free a tile before exiting program.
 */
void free_tile(struct tile *t);

#endif /* TILE_H */
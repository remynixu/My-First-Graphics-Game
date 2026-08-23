#ifndef TILE_H
#define TILE_H

#include "primitives/texture.h"
#include "primitives/types.h"

/*
 * Adding a new tiles means you have to update:
 * - tile.h
 * - collision.h
 * - tile/
 */
enum tile_type{
    TILE_NULL   = 0,
    TILE_STONE,
    TILE_GRASS,
    TILE_WATER,
    MAX_TILE_TYPE
};

/*
 * Pixel-sized tile, doesn't expect to be scaled.
 */
struct tile{
    enum tile_type type;
    int x;
    int y;
};

/*
 * Loads all tiles to memory.
 *
 * RETURN VALUES
 * - -1 -> -x = Index of failed texture.
 * - 1 = Fallback texture fail.
 */
int tile_init(void);

/* Free loaded tiles from memory. */
void tile_quit(void);

#endif /* TILE_H */
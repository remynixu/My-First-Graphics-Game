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

enum tile_state{
    TILE_NORMAL,
    TILE_PAUSED
};

/*
 * Pixel-sized tile, doesn't expect to be scaled.
 */
struct tile{
    enum tile_type type;
    enum tile_state state;
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

/* Max tile width. */
#define TILE_MAXWIDTH   16

/* Max tile height. */
#define TILE_MAXHEIGHT  12

/* Gives a proper texture for a corresponding tile. */
struct texture tile_gettex(struct tile *t);

/* Free loaded tiles from memory. */
void tile_quit(void);

#endif /* TILE_H */
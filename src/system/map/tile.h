#ifndef TILE_H
#define TILE_H

#include <raylib.h>

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
/*
 * - From collision.h
 * Past this point, the tiles are collidable.
 */
    TILE_WATER,
    MAX_TILE_TYPE
};

#define TILE_PIXEL_WIDTH    16
#define TILE_PIXEL_HEIGHT   12

struct tile{
    enum tile_type type;
    int x;
    int y;
};

Rectangle get_tile_hitbox(const struct tile *const t);

/*
 * RETURN VALUES
 * -1 -> -x = Index of failed texture.
 * 1 = Fallback texture fail.
 */

int load_tile_textures(void);

/*
 * The current implementation needs this file to have external help :<
 *
 * This variable expects:
 * - To be incremented with the value of delta time.
 * - Values greater than 0.0f, and less than or equal to 1.0f.
 */

extern float tile_animation_time;

/*
 * Returns a src_hint for draw_tile()! :D
 */

Rectangle prepare_tile(const struct tile *const t, const int seed);
void draw_tile(const struct tile *const t, Rectangle src_hint);

void free_tile_textures(void);

#endif /* TILE_H */
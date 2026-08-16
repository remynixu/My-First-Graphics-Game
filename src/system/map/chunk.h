#ifndef CHUNK_H
#define CHUNK_H

#include "tile.h"

#define MAX_CHUNK_WIDTH     32
#define MAX_CHUNK_HEIGHT    32

struct chunk{
    struct tile tiles[MAX_CHUNK_HEIGHT][MAX_CHUNK_WIDTH];
};

/*
 * Return Values:
 *  0 = Success!
 * -1 = File doesn't exist.
 * -2 = Unreadable header. 
 * -3 = Invalid header.
 * -4 = Incomplete data.
 * -5 = Missing colon separator.
 */

int parse_chunk(const char *const filename, struct chunk *const chunk);

/*
 * Draws an array of array of tiles...
 *
 * ._.
 */

void draw_chunk(const struct chunk *const chunk);

#endif /* CHUNK_H */
#ifndef CHUNK_H
#define CHUNK_H

#include "tile.h"

#define MAX_CHUNK_WIDTH     32
#define MAX_CHUNK_HEIGHT    32

struct chunk{
    struct tile tiles[MAX_CHUNK_HEIGHT][MAX_CHUNK_WIDTH];
};

int parse_chunk(const char *filename, struct chunk *chunk);
void draw_chunk(struct chunk *chunk);

#endif /* CHUNK_H */
#include "chunk.h"

#include <stdio.h>
#include <string.h>

int parse_chunk(const char *const filename, struct chunk *const chunk){
    FILE *f = fopen(filename, "r");
    char magic[6] = {0};
    int r, c;
    if(!f)
        return -1; /* file may not exist */
    if(fscanf(f, "%5s", magic) != 1){
        fclose(f);
        return -2; /* unreadable header */
    }
    if(strcmp(magic, "CHUNK") != 0){
        return -3; /* invalid header */
    }
    for(c = 0; c < MAX_CHUNK_HEIGHT; c++){
        for(r = 0; r < MAX_CHUNK_WIDTH; r++){
            if(fscanf(f, "%u", &chunk->tiles[c][r].type) != 1){
                fclose(f);
                return -4; /* incomplete/corrupt/invalid data */
            }
            chunk->tiles[c][r].x = r * TILE_PIXEL_WIDTH;
            chunk->tiles[c][r].y = c * TILE_PIXEL_HEIGHT;
            if(r < MAX_CHUNK_WIDTH - 1){
                if(fgetc(f) != ':'){
                    fclose(f);
                    return -5; /* missing colon separator */
                }
            }
        }
        fgetc(f); /* skip trailing newline */
    }
    return 0;
}

void draw_chunk(const struct chunk *const chunk){
    int c, r;
    for(c = 0; c < MAX_CHUNK_HEIGHT; c++){
        for(r = 0; r < MAX_CHUNK_WIDTH; r++)
            draw_tile(&chunk->tiles[c][r]);
    }
}
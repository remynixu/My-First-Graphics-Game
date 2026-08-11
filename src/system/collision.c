#include "collision.h"

int check_collision(struct entity *e, struct chunk *chunk){
    int c, r;
    for(c = 0; c < MAX_CHUNK_HEIGHT; c++){
        for(r = 0; r < MAX_CHUNK_WIDTH; r++){
            struct tile *t = &chunk->tiles[c][r];
            switch(t->type){
                case TILE_STONE_WALL:
                if(CheckCollisionRecs(get_entity_hitbox(e), get_tile_hitbox(t)))
                     return 1;
                case TILE_NULL:
                continue;
                default:
                continue;
            }
        }
    }
    return 0;
}
#include "collision.h"

int check_etoc_collision(struct entity *e, struct chunk *chunk){
    int c, r;
    for(c = 0; c < MAX_CHUNK_HEIGHT; c++){
        for(r = 0; r < MAX_CHUNK_WIDTH; r++){
            struct tile *t = &chunk->tiles[c][r];
            switch(t->type){
                case TILE_WATER:
                if(CheckCollisionRecs(get_entity_hitbox(e), get_tile_hitbox(t)))
                     return 1;
                continue;
                case TILE_STONE:
                case TILE_NULL:
                default:
                continue;
            }
        }
    }
    return 0;
}

int check_etoe_collision(struct entity *e, struct entity *list){
    int i;
    for(i = 0; i < MAX_ENTITY_COUNT; i++){
        struct entity *e2 = &list[i];
        switch(e2->type){
            case ENTITY_PLAYER:
            if(CheckCollisionRecs(get_entity_hitbox(e), get_entity_hitbox(e2)))
                 return 1;
            continue;
            case ENTITY_NULL:
            default:
            continue;
        }
    }
    return 0;
}
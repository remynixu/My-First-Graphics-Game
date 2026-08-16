#include "collision.h"

int check_etoc_collision(struct entity *e, struct chunk *chunk){
    Rectangle hb = get_entity_hitbox(e);
    int c, r;
    for(c = 0; c < MAX_CHUNK_HEIGHT; c++){
        for(r = 0; r < MAX_CHUNK_WIDTH; r++){
            struct tile *t = &chunk->tiles[c][r];
            if(t->type < TILE_WATER)
                continue;
            if(CheckCollisionRecs(hb, get_tile_hitbox(t)))
                 return 1;
        }
    }
    return 0;
}

#include <string.h>

int check_etoe_collision(struct entity *e, struct entity *list){
    Rectangle hb = get_entity_hitbox(e);
    int i;
    {
        hb.y += hb.height - hb.height / 2.0f;
        hb.height /= 16.0f;
    }
    for(i = 0; i < MAX_ENTITY_COUNT; i++){
        struct entity *e2 = &list[i];
        if(e2->type < ENTITY_PLAYER)
            continue;
        if(memcmp(e, e2, sizeof(*e)) == 0)
            continue;
        if(CheckCollisionRecs(hb, get_entity_hitbox(e2)))
            return 1;
    }
    return 0;
}
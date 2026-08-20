#include "entity_list.h"

static void _sort(struct entity *const e){
    int i;
    int j;
    struct entity target;
    for(i = 1; i < MAX_ENTITY_COUNT; i++){
        target = e[i];
        for(j = i - 1; j > -1 && e[j].pos.y > target.pos.y; j--)
            e[j + 1] = e[j];
        e[j + 1] = target;
    }
}

#include <string.h>

void draw_entities(const struct entity *const list){
    int i;
    struct entity el[MAX_ENTITY_COUNT];
    memcpy(el, list, sizeof(*el) * MAX_ENTITY_COUNT);
    _sort(el);
    for(i = 0; i < MAX_ENTITY_COUNT; i++){
        if(el[i].type == ENTITY_NULL)
            continue;
        draw_entity(&el[i]);
    }
}

#include <stdio.h>
#include "chunk.h"

int parse_spawntable(const char *filename, struct entity *const list){
    FILE *f = fopen(filename, "r");
    char magic[12] = {0};
    int r, c;
    if(!f)
        return -1; /* file may not exist */
    if(fscanf(f, "%11s", magic) != 1){
        fclose(f);
        return -2; /* unreadable header */
    }
    if(strcmp(magic, "SPAWNTABLE") != 0){
        return -3; /* invalid header */
    }
    for(c = 0; c < MAX_CHUNK_HEIGHT; c++){
        for(r = 0; r < MAX_CHUNK_WIDTH; r++){
            int i = (c * MAX_CHUNK_WIDTH) + r;
            if(fscanf(f, "%u", &list[i].type) != 1){
                fclose(f);
                return -4; /* incomplete/corrupt/invalid data */
            }
            list[i].pos.x = r * TILE_PIXEL_WIDTH;
            list[i].pos.y = c * TILE_PIXEL_HEIGHT;
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
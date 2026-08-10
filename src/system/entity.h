#ifndef ENTITY_H
#define ENTITY_H

#include "engine.h"

enum entity_type{
    ENTITY_NULL = 0,
    ENTITY_PLAYER,
    MAX_ENTITY_TYPE
};

struct entity{
    Vector2 pos;
    enum entity_type type;
    float scale;
};

int load_entity_textures(void);
void draw_entity(struct entity *e);
void free_entity_textures(void);

#endif /* ENTITY_H */
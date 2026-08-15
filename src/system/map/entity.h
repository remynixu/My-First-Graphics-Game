#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

enum entity_type{
    ENTITY_NULL = 0,
    ENTITY_PLAYER,
    MAX_ENTITY_TYPE
};

enum entity_direction{
    ENTITY_UP = 0,
    ENTITY_DOWN,
    ENTITY_LEFT,
    ENTITY_RIGHT
};

struct entity{
    Vector2 pos;
    enum entity_type type;
    enum entity_direction direction;
    float speed;
};

Rectangle get_entity_hitbox(struct entity *e);

int load_entity_textures(void);
void setup_entity(int x, int y, enum entity_type type, struct entity *e);
void draw_entity(struct entity *e);
void free_entity_textures(void);

#define MAX_ENTITY_COUNT    32

void draw_entities(struct entity *list);

#endif /* ENTITY_H */
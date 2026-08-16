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

/*
 * Actually returns an entity's valid hitbox :>
 */

Rectangle get_entity_hitbox(const struct entity *const e);

/*
 * An initializer function, must be done first!
 */

int load_entity_textures(void);

/*
 * Basically sets up an entity, guarantees a valid entity :D
 */

void setup_entity(const int x, const int y, const enum entity_type type, struct entity *const e);

/*
 * Draws an entity ._.
 */

void draw_entity(const struct entity *const e);

/*
 * It doesn't actually uses free(), it just unloads the textures from VRAM.
 */

void free_entity_textures(void);

#define MAX_ENTITY_COUNT    32

/*
 * The list passed on this function is NOT guaranteed to be unaltered after
 * call.
 * 
 * Oh, also... don't you dare pass a list that ISN'T as big as MAX_ENTITY_COUNT!
 */

void draw_entities(const struct entity *const list);

/*
 * This function depends on chunk.h as it shares a common design with its file
 * format, this is to make editing spawntables more intuitive.
 */

int parse_spawntable(const char *filename, struct entity *const list);

#endif /* ENTITY_H */
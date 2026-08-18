#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

/*
 * - From entity_metadata.h
 * Adding another type of entity requires adding its respective metadata in
 * entity_metadata.h.
 */

/*
 * Recognized entities.
 */

enum entity_type{
/* - From draw_entities()
 * Special case, ENTITY_NULL doesn't render.
 */
    ENTITY_NULL = 0,
/*
 * - From collision.h
 * Past this point, the entities are collidable.
 */
    ENTITY_PLAYER,
    ENTITY_ROCK,
    MAX_ENTITY_TYPE
};

/*
 * For sprites, specifically the direction they're facing.
 */

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

#define ENTITY_HITBOX_THICKNESS 0.25f
#define ENTITY_HITBOX_COLOR     RED

/*
 * Draws a red line indicating an entity's hitbox.
 */

void draw_entity_hitbox(const struct entity *const e);

/*
 * An initializer function, must be done first!
 */

int load_entity_textures(void);

/*
 * Basically sets up an entity, guarantees a valid entity :D
 */

void setup_entity(const struct entity *const hint, struct entity *const e);

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

/* DEPRECATED - TO BE REMADE SOON
 *
 * This function depends on chunk.h as it shares a common design with its file
 * format, this is to make editing spawntables more intuitive.
 */

int parse_spawntable(const char *filename, struct entity *const list);

#endif /* ENTITY_H */
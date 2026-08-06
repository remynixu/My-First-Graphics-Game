#ifndef ENTITY_H
#define ENTITY_H

#include "game.h"

struct entity{
    Rectangle hitbox;
    Color color;
};

struct entity_list{
    struct entity *list;
    unsigned long n;
};

/*
 * Checks the entities' collisions first.
 */
void checkcollision_entities(struct entity_list *list);

/*
 * Draws the presumably valid entities (Recommended to be the same list as what
 * checkcollision_entities() used!).
 */
void draw_entities(struct entity_list *list);

#endif /* ENTITY_H */
#ifndef ENTITY_LIST_H
#define ENTITY_LIST_H

#include "primitive/entity.h"

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

#endif /* ENTITY_LIST_H */
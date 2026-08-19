#ifndef COLLISION_H
#define COLLISION_H

#include "map/primitive/entity.h"
#include "map/chunk.h"

int check_etoc_collision(struct entity *e, struct chunk *chunk);
int check_etoe_collision(struct entity *e, struct entity *list);

#endif /* COLLISION_H */
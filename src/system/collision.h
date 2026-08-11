#ifndef COLLISION_H
#define COLLISION_H

#include "entity/entity.h"
#include "map/chunk.h"

int check_collision(struct entity *e, struct chunk *chunk);

#endif /* COLLISION_H */
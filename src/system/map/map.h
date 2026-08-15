#ifndef MAP_H
#define MAP_H

#include "chunk.h"
#include "entity.h"

/*
 * Current data structure plan:
 * - world -> map -> chunks -> tiles
 *              `--> entity
 * - city -> south province -> {abandoned town, mysterious altar -> {goop, altar, floor}}
 *                        `--> {zombies, ghosts, werewolves}
 */

/*
 * Note:
 * - Tiles are strictly floors only, it will always be below entities.
 */

#endif /* MAP_H */
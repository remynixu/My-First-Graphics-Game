#ifndef PLAYER_H
#define PLAYER_H

#include "entity/entity.h"
#include "engine.h"

enum player_direction{
    PLAYER_UP = 0,
    PLAYER_DOWN,
    PLAYER_LEFT,
    PLAYER_RIGHT
};

struct player{
    struct entity display;
    enum player_direction direction;
    float speed;
};

void setup_player(int spawn_x, int spawn_y, struct player *p);
void update_player(struct engine_ctx *ctx, struct player *p);

#endif /* PLAYER_H */
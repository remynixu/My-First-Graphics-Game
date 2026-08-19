#ifndef SCREEN_H
#define SCREEN_H

#include "map/engine.h"

struct screen{
    RenderTexture2D target;
    Rectangle src;
    Rectangle dst;
};

void setup_screen(struct engine_ctx *ctx, struct screen *scr);
void draw_screen(struct screen *scr);
void end_screen(struct screen *scr);

#endif /* SCREEN_H */
#ifndef SCREEN_H
#define SCREEN_H

#include "primitives/texture.h"
#include "primitives/types.h"

#include "env/window.h"

struct screen_info{
    struct texture_info texinfo;
    struct texture_info depth;
    unsigned int id;
};

struct screen{
    struct screen_info info;
    struct draw_modifier pos;   /* Affects where the screen is drawn instead. */
};

/* Loads a screen you can "draw" on to memory without "requiring" a window. */
void screen_make(struct screen *scr, struct vector2 info);

/* Makes a screen the size of the window (also initializes the game's window). */
int screen_init(struct screen *scr, struct window_info *info);

/* Begins the state that allows rendering functions to draw within a screen. */
void screenmode_begin(struct screen *scr);

/* Ends the state that allows rendering functions to draw within a screen. */
void screenmode_end(void);

/* Draws what's rendered in the specified screen. */
void screen_update(struct screen *scr);

/* Unloads the screen from memory. */
void screen_quit(struct screen *scr);

#endif /* SCREEN_H */
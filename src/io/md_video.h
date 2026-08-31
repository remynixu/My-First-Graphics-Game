#ifndef MD_VIDEO_H
#define MD_VIDEO_H

/*
 * This header's only job is to offer a way for the engine to output its visuals
 * to the platform's screen.
 * 
 * This means that it's up to the engine to do the manual blitting of the pixels
 * to mi_video_ram.
 */

#include "mi_pixel.h"

/*
 * These two macros will define the engine's screen separate from the platform's
 * screen size.
 */

/* The engine video ram's pixel width. */
#define MI_PIXEL_BUFFER_WIDTH   640

/* The engine video ram's pixel height. */
#define MI_PIXEL_BUFFER_HEIGHT  480

/* The engine video ram's final size. */
#define MI_VIDEO_RAM_BUFFER_SIZE    (MI_PIXEL_BUFFER_HEIGHT * MI_PIXEL_BUFFER_WIDTH * MI_PIXEL_BYTE_SIZE)

/*
 * This video ram is for the engine's core, we don't know/need to know how big
 * the platform's screen is anyways—we leave it up to the implementation.
 */

struct mi_video_ram{
    byte buffer[MI_VIDEO_RAM_BUFFER_SIZE];
};

/*
 * Initializes the video's "screen." Also initializes the parameter into a valid
 * video ram for our engine.
 * 
 * Returns an implementation-defined error code, pass the value to
 * md_video_strerror for more info.
 */

int md_video_init(struct mi_video_ram *vram);

/*
 * Returns a message about the error code returned from functions *only* within
 * this header.
 */

const char *md_video_strerror(int errcode);

/*
 * Clears the *engine*'s "screen."
 */

void md_video_clear(struct mi_video_ram *mi_vram);

/*
 * Puts the contents of our *valid* video ram to the platform's screen.
 */

void md_video_from_vram(struct mi_video_ram *vram);

#endif /* MD_VIDEO_H */
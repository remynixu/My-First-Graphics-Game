#ifndef MD_VIDEO_H

/*
 * This header's only job is to offer a way for the engine to output its visuals
 * to the platform's screen.
 * 
 * This means that it's up to the engine to do the manual blitting of the pixels
 * to md_video_ram.
 */
#define MD_VIDEO_H

#include "md_pixel.h"

/*
 * These two macros will define the engine's screen separate from the platform's
 * screen size. These macros are actually independent from the platform! :D
 */

/* The engine video ram's pixel width. */
#define MI_PIXEL_BUFFER_WIDTH   640

/* The engine video ram's pixel height. */
#define MI_PIXEL_BUFFER_HEIGHT  480

/*
 * Since pixels aren't exactly one byte and is rather the size of
 * MD_PIXEL_BYTE_SIZE, we take it into account—a pixel can be any size in
 * different platforms.
 */

/* The engine video ram's final size. */
#define MD_VIDEO_RAM_BUFFER_SIZE    (MI_PIXEL_BUFFER_HEIGHT * MI_PIXEL_BUFFER_WIDTH * MD_PIXEL_BYTE_SIZE)

/*
 * This video ram is for the engine's core, we don't know/need to know how big
 * the platform's screen is anyways—we leave it up to the implementation.
 */
struct md_video_ram{
    byte buffer[MD_VIDEO_RAM_BUFFER_SIZE];
};

/*
 * Initializes the video's "screen." Also initializes the parameter into a valid
 * video ram for our engine to use.
 * 
 * Returns an implementation-defined error code, pass the value to
 * md_video_strerror for more info.
 */
int md_video_init(struct md_video_ram *md_vram);

/*
 * Returns a message about the error code returned from functions *only* within
 * this header.
 */
const char *md_video_strerror(int errcode);

/*
 * Clears the *engine*'s "screen."
 */
void md_video_clear(struct md_video_ram *md_vram);

/*
 * Puts the contents of our *valid* video ram to the platform's screen.
 */
void md_video_from_vram(struct md_video_ram *md_vram);

/*
 * Cleans up the video's "screen." Also cleans up the *valid* video ram provided
 * by the parameter.
 */
void md_video_quit(struct md_video_ram *md_vram);

#endif /* MD_VIDEO_H */
#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#ifndef GAME_TITLE
    #define GAME_TITLE  "Arundel"
#endif /* GAME_TITLE */

/*
 * The first three variables will not be updated by update_gamestate().
 * It must be manually set.
 */
struct game_state{
    int screen_width;
    int screen_height;
    int target_fps;
    float delta_time;
    unsigned char heldkey_flags;
};

/*
 * Flags to check for game_state's held_keysflag member.
 */
enum heldkey_flags{
    KEYCODE_W = (1 << 0),
    KEYCODE_S = (1 << 1),
    KEYCODE_A = (1 << 2),
    KEYCODE_D = (1 << 3),
    KEYCODE_SPC = (1 << 4),
    KEYCODE_Q = (1 << 5),
    KEYCODE_F = (1 << 6),
    KEYCODE_R = (1 << 7)
};

 /*
  * Uses game_state to initialize the game.
  */
void init_game(struct game_state *gs);

/*
 * Updates the game state's variables so they can be used by other systems.
 */
void update_gamestate(struct game_state *gs);

/*
 * Don't forget to call this before leaving.
 */
void cleanup_game(void);

#endif /* GAME_H */
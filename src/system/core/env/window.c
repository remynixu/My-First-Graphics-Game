#include "window.h"

#include <raylib.h>

int window_init(struct screen_info *scr){
    if(!ChangeDirectory(GetApplicationDirectory()))
        return -1;
    InitWindow(scr->width, scr->height, scr->title);
    return 0;
}

void window_quit(void){
    CloseWindow();
}
#include "window.h"

#include <raylib.h>

int window_init(struct window_info *info){
    if(!ChangeDirectory(GetApplicationDirectory()))
        return -1;
    InitWindow(info->width, info->height, info->title);
    return 0;
}

void window_quit(void){
    CloseWindow();
}
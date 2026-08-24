#ifndef WINDOW_H
#define WINDOW_H

#define WINDOWTITLE_MAXSTRLEN   16

struct window_info{
    unsigned int width;
    unsigned int height;
    char title[WINDOWTITLE_MAXSTRLEN];
};

int window_init(struct window_info *info);
void window_quit(void);

#endif /* WINDOW_H */
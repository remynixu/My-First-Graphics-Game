#ifndef ENV_H
#define ENV_H

#define SCREENTITLE_MAXSTRLEN   16

struct screen_info{
    unsigned int width;
    unsigned int height;
    char title[SCREENTITLE_MAXSTRLEN];
};

#endif /* ENV_H */
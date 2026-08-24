#ifndef TYPES_H
#define TYPES_H

struct vector2{
    int x;
    int y;
};

struct vector2 tovec2(int x, int y);

struct rectangle{
    int width;
    int height;
    int x;
    int y;
};

#ifdef _TYPES_CONVERTIONS

#define implvec2_to_vec2(implvec2, vec2)    \
do{                                         \
    (vec2).x = (implvec2).x;                    \
    (vec2).y = (implvec2).y;                    \
}while(0)

#define implrec_to_rec(implrec, rec)    \
do{                                     \
    (rec).x = (implrec).x;                  \
    (rec).y = (implrec).y;                  \
    (rec).width = (implrec).width;          \
    (rec).height = (implrec).height;        \
}while(0)

#endif /* _TYPES_CONVERTIONS */

#endif /* TYPES_H */
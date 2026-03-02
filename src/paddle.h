#ifndef PADDLE_H
#define PADDLE_H

#include "bh.h"

#define PADDLE_WIDTH 16.0f
#define PADDLE_HEIGHT 64.0f

extern Paddle *PADDLE_ALL[];

enum PaddleSide_e {
    PADDLE_SIDE_LEFT = 0,
    PADDLE_SIDE_RIGHT = 1
};

struct Paddle_s {
    Vector2 ul_corner;
    PaddleSide side;
};

void Paddle_all_init(void);
void Paddle_all_cleanup(void);
void Paddle_all_update(void);
void Paddle_all_draw(void);
Paddle *Paddle_init(PaddleSide side);
void Paddle_del(Paddle *p);

#endif

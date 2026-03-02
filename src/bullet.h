#ifndef BULLET_H
#define BULLET_H

#include "bh.h"

#define BULLET_MAX_BULLETS 40
#define BULLET_SPEED 4.0f

extern Bullet *BULLET_ALL[];

struct Bullet_s {
    Vector2 pos;
    Vector2 vel;
    uint32_t bullet_idx;
    uint32_t time_alive;
};

void Bullet_all_init(void);
void Bullet_all_cleanup(void);
void Bullet_all_update(void);
void Bullet_all_draw(void);
Bullet *Bullet_init(Vector2 pos, Vector2 vel);
void Bullet_del(Bullet *b);

#endif

#ifndef UFO_H
#define UFO_H

#include "bh.h"

#define UFO_RADIUS_INNER 8.0f
#define UFO_RADIUS_OUTER 16.0f
#define UFO_START_SPEED 0.5f
#define UFO_SPEED_INC 0.0001f

struct UFO_s {
    Vector2 pos;
    float speed;
};

UFO *UFO_init(Vector2 pos);
void UFO_del(UFO *u);
void UFO_update(UFO *u, Ship *d);
void UFO_draw(UFO *u);

#endif

#ifndef SHIP_H
#define SHIP_H

#include "bh.h"

struct Ship_s {
    Vector2 center;
    Vector2 points[3];
    float angle;
};

Ship *Ship_init(Vector2 center);
void Ship_del(Ship *s);
void Ship_turn(Ship *s, float rad);
void Ship_thrust(Ship *s, float a);
void Ship_draw(Ship *s);

#endif

#ifndef SHIP_H
#define SHIP_H

#include "bh.h"

#define SHIP_RADIUS 16.0f
#define SHIP_HIT_RADIUS 8.0f
#define SHIP_TERMINAL_VELOCITY 8.0f

struct Ship_s {
    Vector2 center;
    Vector2 vel;
    Vector2 accel;
    Vector2 points[3];
    Vector2 facing;
    float angle;
    bool exploded;
};

Ship *Ship_init(Vector2 center);
void Ship_del(Ship *s);
void Ship_turn(Ship *s, float rad);
void Ship_thrust(Ship *s, float a);
void Ship_draw(Ship *s);
void Ship_update(Ship *s);
void Ship_fire(Ship *s);
void Ship_explode(Ship *s);

#endif

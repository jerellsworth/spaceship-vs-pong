#include "bh.h"

UFO *UFO_init(Vector2 pos) {
    UFO *u = calloc(1, sizeof(UFO));
    u->pos = pos;
    u->speed = UFO_START_SPEED;
    return u;
}

void UFO_del(UFO *u) {
    free(u);
}

void UFO_update(UFO *u, Ship *s) {
    if (s->exploded) return;
    float dist = Vector2Distance(s->center, u->pos);
    if (dist < SHIP_HIT_RADIUS + UFO_RADIUS_INNER) {
        Ship_explode(s);
        return;
    }
    Vector2 dpos = Vector2Subtract(s->center, u->pos); 
    Vector2 vel = Vector2Scale(Vector2Normalize(dpos), u->speed);
    u->pos = Vector2Add(u->pos, vel);
    u->speed += UFO_SPEED_INC;
}

void UFO_draw(UFO *u) {
    DrawRing(
        u->pos,
        UFO_RADIUS_INNER, 
        UFO_RADIUS_OUTER,
        0.0f,
        360.0f,
        360, 
        BLACK
    );
}

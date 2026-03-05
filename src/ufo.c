#include "bh.h"

UFO *UFO_init(Vector2 pos) {
    UFO *u = calloc(1, sizeof(UFO));
    u->pos = pos;
    u->speed = UFO_START_SPEED;
}

void UFO_del(UFO *u) {
    free(u);
}

void UFO_update(UFO *u) {
    // TODO stub
}

void UFO_draw(UFO *u) {
    DrawRing(
        u->pos,
        UFO_RADIUS_INNER, 
        UFO_RADIUS_OUTER,
        0,
        2 * PI,
        1,
        BLACK
    );
}

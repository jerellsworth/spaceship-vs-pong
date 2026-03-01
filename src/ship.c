#include "bh.h"

Ship *Ship_init(Vector2 center) {
    Ship *s = calloc(1, sizeof(Ship));
    s->center = center;
    s->points[0] = Vector2Add(center, (Vector2){8.0f, 0.0f});
    s->points[1] = Vector2Add(center, (Vector2){-4.0f, 6.93f});
    s->points[2] = Vector2Add(center, (Vector2){-4.0f, -6.93f});
    return s;
}

void Ship_del(Ship *s) {
    free(s);
}

void Ship_turn(Ship *s, float rad) {
    for (int i = 0; i < 3; ++i) {
        s->points[i] = Vector2Add(s->center, Vector2Rotate(Vector2Subtract(s->points[i], s->center), rad));
    }
}

void Ship_thrust(Ship *s, float a) {
    //TODO stub
}

void Ship_draw(Ship *s) {
    DrawTriangle(
        s->points[2],
        s->points[1],
        s->points[0],
        BLACK
    );
}

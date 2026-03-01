#include "bh.h"

Ship *Ship_init(Vector2 center) {
    Ship *s = calloc(1, sizeof(Ship));
    s->center = center;
    s->points[0] = Vector2Add(center, (Vector2){8.0f, 0.0f});
    float angle = (2.0f * PI) * (5.0f / 12.0f);
    s->points[1] = Vector2Add(center, (Vector2){cosf(angle) * 8.0f, sinf(angle) * 8.0f});
    angle = (2.0f * PI) * (7.0f / 12.0f);
    s->points[2] = Vector2Add(center, (Vector2){cosf(angle) * 8.0f, sinf(angle) * 8.0f});
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
    if (a == 0) {
        s->accel = (Vector2){0.0f, 0.0f};
        return;
    }
    s->accel = Vector2Scale(Vector2Normalize(Vector2Subtract(s->points[0], s->center)), a);
}

void Ship_update(Ship *s) {
    s->vel = Vector2Add(s->vel, s->accel);
    s->center = Vector2Add(s->center, s->vel);
    for (int i = 0; i < 3; ++i) {
        s->points[i] = Vector2Add(s->points[i], s->vel);
    }
}

void Ship_draw(Ship *s) {
    DrawTriangle(
        s->points[2],
        s->points[1],
        s->points[0],
        BLACK
    );
}

#include "bh.h"

Ship *Ship_init(Vector2 center) {
    Ship *s = calloc(1, sizeof(Ship));
    s->center = center;
    s->points[0] = Vector2Add(center, (Vector2){SHIP_RADIUS, 0.0f});
    float angle = (2.0f * PI) * (5.0f / 12.0f);
    s->points[1] = Vector2Add(center, (Vector2){cosf(angle) * SHIP_RADIUS, sinf(angle) * SHIP_RADIUS});
    angle = (2.0f * PI) * (7.0f / 12.0f);
    s->points[2] = Vector2Add(center, (Vector2){cosf(angle) * SHIP_RADIUS, sinf(angle) * SHIP_RADIUS});
    return s;
}

void Ship_del(Ship *s) {
    free(s);
}

void Ship_turn(Ship *s, float rad) {
    for (uint32_t i = 0; i < 3; ++i) {
        s->points[i] = Vector2Add(s->center, Vector2Rotate(Vector2Subtract(s->points[i], s->center), rad));
    }
}

Vector2 _Ship_facing_vector(Ship *s, float scale) {
    return Vector2Scale(Vector2Normalize(Vector2Subtract(s->points[0], s->center)), scale);
}

void Ship_thrust(Ship *s, float a) {
    if (a == 0) {
        s->accel = (Vector2){0.0f, 0.0f};
        return;
    }
    s->accel = _Ship_facing_vector(s, a);
    Vector2 dpos = Vector2Subtract(s->points[2], s->points[1]);
    dpos.x /= 16.0f;
    dpos.y /= 16.0f;
    Vector2 pos = s->points[1];
    for (uint32_t i = 0; i < 17; ++i) {
        FireParticle_init(pos, (Vector2){0.0f, 0.0f});
        pos = Vector2Add(pos, dpos);
    }
}

void Ship_update(Ship *s) {
    if (!s) return;
    if (s->exploded) return;
    s->vel = Vector2Add(s->vel, s->accel);
    float magnitude = Vector2Length(s->vel);
    if (magnitude > SHIP_TERMINAL_VELOCITY) {
        s->vel = Vector2Scale(Vector2Normalize(s->vel), SHIP_TERMINAL_VELOCITY);
    }
    Vector2 next_center = Vector2Add(s->center, s->vel);
    if (next_center.x <= PLAYFIELD_MIN_X) {
        next_center.x = PLAYFIELD_MIN_X;
        s->vel.x = -s->vel.x;
    } else if (next_center.x >= PLAYFIELD_MAX_X) {
        next_center.x = PLAYFIELD_MAX_X;
        s->vel.x = -s->vel.x;
    }
    if (next_center.y <= PLAYFIELD_MIN_Y) {
        next_center.y = PLAYFIELD_MIN_Y;
        s->vel.y = -s->vel.y;
    } else if (next_center.y >= PLAYFIELD_MAX_Y) {
        next_center.y = PLAYFIELD_MAX_Y;
        s->vel.y = -s->vel.y;
    }
    Vector2 dpos = Vector2Subtract(next_center, s->center);
    s->center = next_center;

    for (uint32_t i = 0; i < 3; ++i) {
        s->points[i] = Vector2Add(s->points[i], dpos);
    }

    for (uint32_t i = 0; i < BULLET_MAX_BULLETS; ++i) {
        Bullet *b = BULLET_ALL[i];
        if (!b) continue;
        if (b->time_alive < 15) continue;
        if (fabsf(b->pos.x - s->center.x) > SHIP_RADIUS) continue;
        if (fabsf(b->pos.y - s->center.y) > SHIP_RADIUS) continue;
        float dist = Vector2Distance(s->center, b->pos);
        if (dist <= SHIP_HIT_RADIUS) {
            for (float rad = 0; rad < 2 * PI; rad += 2 * PI / 64) {
                Vector2 vel = (Vector2){cosf(rad), sinf(rad)};
                FireParticle_init(s->center, vel);
                vel = (Vector2){vel.x / 2, vel.y / 2};
            }
            s->exploded = 1;        
            return;
        }
    }

}

void Ship_draw(Ship *s) {
    if (!s) return;
    if (s->exploded) return;
    DrawTriangle(
        s->points[2],
        s->points[1],
        s->points[0],
        BLACK
    );
}

void Ship_fire(Ship *s) {
    Vector2 pos = s->points[0];
    Vector2 vel = _Ship_facing_vector(s, BULLET_SPEED);
    Bullet_init(pos, vel);
}

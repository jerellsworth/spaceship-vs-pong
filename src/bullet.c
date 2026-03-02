#include "bh.h"

Bullet *BULLET_ALL[BULLET_MAX_BULLETS];

void Bullet_all_init(void) {
    for (uint32_t i = 0; i < BULLET_MAX_BULLETS; ++i) {
        BULLET_ALL[i] = NULL;
    }
}

void Bullet_all_cleanup(void) {
    for (uint32_t i = 0; i < BULLET_MAX_BULLETS; ++i) {
        Bullet *b = BULLET_ALL[i];
        if (!b) continue;
        Bullet_del(b);
    }
}

void Bullet_all_update(void) {
    for (uint32_t i = 0; i < BULLET_MAX_BULLETS; ++i) {
        Bullet *b = BULLET_ALL[i];
        if (!b) continue;
        b->pos = Vector2Add(b->pos, b->vel);
        // TODO delete them eventually
    }
}

void Bullet_all_draw(void) {
    for (uint32_t i = 0; i < BULLET_MAX_BULLETS; ++i) {
        Bullet *b = BULLET_ALL[i];
        if (!b) continue;
        DrawCircle(b->pos.x, b->pos.y, 4, BLACK);
    }
}

Bullet *Bullet_init(Vector2 pos, Vector2 vel) {
    for (uint32_t i = 0; i < BULLET_MAX_BULLETS; ++i) {
        if (!BULLET_ALL[i]) {
            Bullet *b = calloc(1, sizeof(Bullet));
            b->pos = pos;
            b->vel = vel;
            b->bullet_idx = i;
            BULLET_ALL[i] = b;
            return b;
        }
    }
    return NULL;
}

void Bullet_del(Bullet *b) {
    BULLET_ALL[b->bullet_idx] = NULL;
    free(b);
}

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

uint32_t Bullet_all_update(UFO *u) {
    uint32_t score_diff = 0;
    for (uint32_t i = 0; i < BULLET_MAX_BULLETS; ++i) {
        Bullet *b = BULLET_ALL[i];
        if (!b) continue;
        ++b->time_alive;
        b->pos = Vector2Add(b->pos, b->vel);
        if (b->pos.x <= PLAYFIELD_MIN_X) {
            Paddle *p = PADDLE_ALL[PADDLE_SIDE_LEFT];
            if (
                p
                && b->pos.y >= p->ul_corner.y
                && b->pos.y <= p->ul_corner.y + PADDLE_HEIGHT
            ) {
                b->pos.x = PLAYFIELD_MIN_X;
                b->vel.x = -b->vel.x;
                Sound_ping();
            } else {
                Bullet_del(b);
                ++score_diff;
                PlaySound(fx_score);
                continue;
            }
        }
        if (b->pos.x >= PLAYFIELD_MAX_X) {
            Paddle *p = PADDLE_ALL[PADDLE_SIDE_RIGHT];
            if (
                p
                && b->pos.y >= p->ul_corner.y
                && b->pos.y <= p->ul_corner.y + PADDLE_HEIGHT
            ) {
                b->pos.x = PLAYFIELD_MAX_X;
                b->vel.x = -b->vel.x;
                Sound_ping();
            } else {
                Bullet_del(b);
                ++score_diff;
                PlaySound(fx_score);
                continue;
            }
        }
        if (b->pos.y <= PLAYFIELD_MIN_Y) {
            b->pos.y = PLAYFIELD_MIN_Y;
            b->vel.y = -b->vel.y;
            Sound_ping();
        } else if (b->pos.y >= PLAYFIELD_MAX_Y) {
            b->pos.y = PLAYFIELD_MAX_Y;
            b->vel.y = -b->vel.y;
            Sound_ping();
        }
    }
    return score_diff;
}

void Bullet_all_draw(void) {
    for (uint32_t i = 0; i < BULLET_MAX_BULLETS; ++i) {
        Bullet *b = BULLET_ALL[i];
        if (!b) continue;
        DrawCircle(b->pos.x, b->pos.y, 4, BLACK);
    }
}

void Bullet_all_mark_bg(RenderTexture2D bg) {
    BeginTextureMode(bg);
    for (uint32_t i = 0; i < BULLET_MAX_BULLETS; ++i) {
        Bullet *b = BULLET_ALL[i];
        if (!b) continue;
        DrawCircle(b->pos.x, b->pos.y, 4, GetColor(0x5DB3D8FF));
    }
    EndTextureMode();
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

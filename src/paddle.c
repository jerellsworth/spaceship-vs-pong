#include "bh.h"

Paddle *PADDLE_ALL[2];

void Paddle_all_init(void) {
    PADDLE_ALL[0] = NULL;
    PADDLE_ALL[1] = NULL;
    Paddle_init(PADDLE_SIDE_LEFT);
    Paddle_init(PADDLE_SIDE_RIGHT);
}

void Paddle_all_cleanup(void) {
    Paddle_del(PADDLE_ALL[0]);
    Paddle_del(PADDLE_ALL[1]);
}

void _Paddle_update(Paddle *p) {
    if (!p) return;
    Bullet *nearest = NULL;
    float nearest_dist = FLT_MAX;
    float center_x = p->ul_corner.x + (PADDLE_WIDTH / 2);
    float center_y = p->ul_corner.y + (PADDLE_HEIGHT / 2);
    for (uint32_t i = 0; i < BULLET_MAX_BULLETS; ++i) {
        Bullet *b = BULLET_ALL[i];
        if (!b) continue;
        if (p->side == PADDLE_SIDE_LEFT && b->vel.x >= 0.0f) continue;
        if (p->side == PADDLE_SIDE_RIGHT && b->vel.x <= 0.0f) continue;
        float dist = fabsf(b->pos.x - center_x);
        if (dist > nearest_dist) continue;
        nearest_dist = dist;
        nearest = b;
    }
    if (!nearest) return;
    float traj = nearest->pos.y - center_y;
    traj = fmaxf(traj, -PADDLE_SPEED);
    traj = fminf(traj, PADDLE_SPEED);
    float next_y = p->ul_corner.y + traj;
    next_y = fmaxf(next_y, 0.0f);
    next_y = fminf(next_y, PLAYFIELD_MAX_Y - PADDLE_HEIGHT);
    p->ul_corner.y = next_y;
}

void Paddle_all_update(void) {
    _Paddle_update(PADDLE_ALL[0]);
    _Paddle_update(PADDLE_ALL[1]);
}

void Paddle_all_draw(void) {
    for (uint32_t i = 0; i < 2; ++i) {
        Paddle *p = PADDLE_ALL[i];
        if (!p) continue;
        DrawRectangle(p->ul_corner.x, p->ul_corner.y, PADDLE_WIDTH, PADDLE_HEIGHT, BLACK); 
    }
}

Paddle *Paddle_init(PaddleSide side) {
    if (PADDLE_ALL[side]) return NULL;
    Paddle *p = calloc(1, sizeof(Paddle));
    p->side = side;
    float x = side == PADDLE_SIDE_LEFT ? PLAYFIELD_PADDLE_MARGIN : PLAYFIELD_MAX_X;
    float y = ((PLAYFIELD_MIN_Y + PLAYFIELD_MAX_Y) / 2.0f) - (PADDLE_HEIGHT / 2.0f);
    p->ul_corner = (Vector2){x, y};
    PADDLE_ALL[side] = p;
    return p;
}

void Paddle_del(Paddle *p) {
    if (!p) return;
    PADDLE_ALL[p->side] = NULL;
    free(p);
}

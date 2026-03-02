#ifndef FIRE_PARTICLE_H
#define FIRE_PARTICLE_H

#include "bh.h"

#define FIRE_PARTICLE_MAX_PARTICLES 100
#define FIRE_PARTICLE_TTL 60

struct FireParticle_s {
    Vector2 pos;
    Vector2 vel;
    uint32_t age;
    uint32_t idx;
};

void FireParticle_all_init(void);
void FireParticle_all_update(void);
void FireParticle_all_draw(void);
void FireParticle_all_cleanup(void);
FireParticle *FireParticle_init(Vector2 pos, Vector2 vel);
void FireParticle_del(FireParticle *fp);

#endif

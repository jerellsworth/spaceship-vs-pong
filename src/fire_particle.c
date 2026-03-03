#include "bh.h"

FireParticle *_FIRE_PARTICLE_ALL[FIRE_PARTICLE_MAX_PARTICLES];
const int _FIRE_PARTICLE_COLORS[] = {
    0xEBFF00FF,
    0xEBC600FF,
    0xD36B00FF,
    0xBE1A00FF
};

void FireParticle_all_init(void) {
    for (uint32_t i = 0; i < FIRE_PARTICLE_MAX_PARTICLES; ++i) {
        _FIRE_PARTICLE_ALL[i] = NULL;
    }
}

void FireParticle_all_update(void) {
    for (uint32_t i = 0; i < FIRE_PARTICLE_MAX_PARTICLES; ++i) {
        FireParticle *fp = _FIRE_PARTICLE_ALL[i];
        if (!fp) continue;
        ++fp->age;
        if (fp->age > FIRE_PARTICLE_TTL) {
            FireParticle_del(fp);
            continue;
        }
        fp->pos = Vector2Add(fp->pos, fp->vel);
    }
}

void FireParticle_all_draw(void) {
    for (uint32_t i = 0; i < FIRE_PARTICLE_MAX_PARTICLES; ++i) {
        FireParticle *fp = _FIRE_PARTICLE_ALL[i];
        if (!fp) continue;
        uint32_t phase = fp->age / (FIRE_PARTICLE_TTL / 4);
        if (phase > 3) phase = 3;
        DrawPixelV(fp->pos, GetColor(_FIRE_PARTICLE_COLORS[phase]));
    }
}

void FireParticle_all_cleanup(void) {
    for (uint32_t i = 0; i < FIRE_PARTICLE_MAX_PARTICLES; ++i) {
        FireParticle *fp = _FIRE_PARTICLE_ALL[i];
        if (!fp) continue;
        FireParticle_del(fp);
    }
}

FireParticle *FireParticle_init(Vector2 pos, Vector2 vel) {
    for (uint32_t i = 0; i < FIRE_PARTICLE_MAX_PARTICLES; ++i) {
        if (!_FIRE_PARTICLE_ALL[i]) {
            FireParticle *fp = calloc(1, sizeof(FireParticle));
            fp->pos = pos;
            fp->vel = vel;
            fp->idx = i;
            _FIRE_PARTICLE_ALL[i] = fp;
            return fp;
        }
    }
    return NULL;
}

void FireParticle_del(FireParticle *fp) {
    _FIRE_PARTICLE_ALL[fp->idx] = NULL;
    free(fp);
}

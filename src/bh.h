#ifndef BH_H
#define BH_H

#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

typedef enum PaddleSide_e PaddleSide;
typedef struct Bullet_s Bullet;
typedef struct Ship_s Ship;
typedef struct Paddle_s Paddle;
typedef struct FireParticle_s FireParticle;

#include "paddle.h"
#include "playfield.h"
#include "ship.h"
#include "bullet.h"
#include "fire_particle.h"

#endif

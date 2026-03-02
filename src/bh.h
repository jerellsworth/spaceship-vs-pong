#ifndef BH_H
#define BH_H

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <math.h>

#include "raylib.h"
#include "raymath.h"

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

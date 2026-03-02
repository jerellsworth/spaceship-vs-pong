/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include "bh.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int endFrame = -1;
static int finishScreen = 0;
Ship *ship = NULL;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    Vector2 center = {(PLAYFIELD_MIN_X + PLAYFIELD_MAX_X) / 2, (PLAYFIELD_MIN_Y + PLAYFIELD_MAX_Y) / 2};
    framesCounter = 0;
    finishScreen = 0;
    Bullet_all_init();
    Paddle_all_init();
    ship = Ship_init(
        center
    );
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!

    // Press enter or tap to change to ENDING screen
    ++framesCounter;
    if (!ship->exploded) {
        if (IsKeyDown(KEY_A))
        {
            Ship_turn(ship, -2.0f * PI / 64.0f);
        } else if (IsKeyDown(KEY_D)) {
            Ship_turn(ship, 2.0f * PI / 64.0f);
        }
        if (IsKeyDown(KEY_W)) {
            Ship_thrust(ship, 0.1f);
        } else {
            Ship_thrust(ship, 0.0f);
        }
        if (IsKeyPressed(KEY_SPACE)) {
            Ship_fire(ship);
        }
        if (IsKeyPressed(KEY_Q)) {
            ship->exploded = 1;
        }
    }

    Ship_update(ship);
    if (ship->exploded && endFrame < 0) {
        endFrame = framesCounter + 120;
    }
    Paddle_all_update();
    Bullet_all_update();
    if (endFrame >= 0 && framesCounter >= endFrame) {
        finishScreen = 1;
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    Ship_draw(ship);
    Paddle_all_draw();
    Bullet_all_draw();
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    Bullet_all_cleanup();
    Ship_del(ship);
    ship = NULL;
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}

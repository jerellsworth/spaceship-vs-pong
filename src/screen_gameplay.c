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
static Color bg_fill_color;
uint32_t score = 0;
Ship *ship = NULL;
RenderTexture2D bg;
Shader bg_shader;
float score_line;
float v_score_line;


//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    bg_fill_color = GetColor(0x0FA0DF08);
    Vector2 center = {(PLAYFIELD_MIN_X + PLAYFIELD_MAX_X) / 2, (PLAYFIELD_MIN_Y + PLAYFIELD_MAX_Y) / 2};
    framesCounter = 0;
    finishScreen = 0;
    endFrame = -1;
    score = 0;
    score_line = -6.0f;
    bg = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    BeginTextureMode(bg);
        ClearBackground(bg_fill_color);
    EndTextureMode();
    Bullet_all_init();
    Paddle_all_init();
    FireParticle_all_init();
    ship = Ship_init(
        center
    );
    bg_shader = LoadShader(0, TextFormat("resources/shaders/glsl%i/bloom.fs", GLSL_VERSION));
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    ++framesCounter;
    UpdateMusicStream(music);
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
    }

    Ship_update(ship);
    if (ship->exploded && endFrame < 0) {
        endFrame = framesCounter + 60;
    }
    Paddle_all_update();
    uint32_t score_diff = Bullet_all_update();
    if (!ship->exploded) {
        if (score_diff > 0) {
            score += score_diff;
            score_line = PLAYFIELD_MIN_Y;
        }
    }
    BeginTextureMode(bg);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), bg_fill_color);
    EndTextureMode();
    Bullet_all_mark_bg(bg);
    FireParticle_all_update();
    if (score_line > -6.0f) {
        score_line -= 2.0f;
    }
    if (endFrame >= 0 && framesCounter >= endFrame) {
        finishScreen = 1;
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    BeginShaderMode(bg_shader);
        DrawTextureRec(
            bg.texture,
            (Rectangle){ 0, 0, (float)bg.texture.width, (float)-bg.texture.height },
            (Vector2) { 0, 0 },
            WHITE
            );
        DrawLineEx(
            (Vector2){PLAYFIELD_MIN_X, score_line},
            (Vector2){PLAYFIELD_MAX_X, score_line},
            6.0f,
            BLACK
        );
    EndShaderMode();
    FireParticle_all_draw();
    Playfield_draw(score);
    Paddle_all_draw();
    Bullet_all_draw();
    Ship_draw(ship);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    Bullet_all_cleanup();
    FireParticle_all_cleanup();
    Paddle_all_cleanup();
    Ship_del(ship);
    ship = NULL;
    UnloadRenderTexture(bg);
    UnloadShader(bg_shader);
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}

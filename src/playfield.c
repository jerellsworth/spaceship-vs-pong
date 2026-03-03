#include "bh.h"

void Playfield_draw(uint32_t score) {
    DrawLineEx(
        (Vector2){PLAYFIELD_MIN_X, PLAYFIELD_MIN_Y},
        (Vector2){PLAYFIELD_MAX_X, PLAYFIELD_MIN_Y},
        2.0,
        BLACK
    );
    const char *score_fmt = TextFormat("%d", score);
    DrawTextEx(font, score_fmt, (Vector2){ PLAYFIELD_MIN_X, 0.0f }, 80, 1, BLACK);

    const char *copyright = "(c) 2026 Safety Stoat Studios";
    Vector2 size = MeasureTextEx(font, copyright, 20, 1.0f);
    DrawTextEx(font, copyright, (Vector2){ PLAYFIELD_MAX_X - size.x, PLAYFIELD_MIN_Y - size.y - 2.0f }, 20, 1.0f, BLACK);
 
    DrawLineEx(
        (Vector2){PLAYFIELD_SHIP_MIN_X, PLAYFIELD_MIN_Y},
        (Vector2){PLAYFIELD_SHIP_MIN_X, PLAYFIELD_MAX_Y},
        1.0,
        BLACK
    );
    DrawLineEx(
        (Vector2){PLAYFIELD_SHIP_MAX_X, PLAYFIELD_MIN_Y},
        (Vector2){PLAYFIELD_SHIP_MAX_X, PLAYFIELD_MAX_Y},
        1.0,
        BLACK
    );
}

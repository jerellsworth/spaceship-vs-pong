#include "bh.h"

void Playfield_draw(uint32_t score) {
    DrawLineEx(
        (Vector2){PLAYFIELD_MIN_X, PLAYFIELD_MIN_Y},
        (Vector2){PLAYFIELD_MAX_X, PLAYFIELD_MIN_Y},
        2.0,
        BLACK
    );
    char buf[32];
    snprintf(buf, 32, "%d", score);
    DrawText(buf, PLAYFIELD_MIN_X, 10, 40, BLACK);
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

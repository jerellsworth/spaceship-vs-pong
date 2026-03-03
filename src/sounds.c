#include "bh.h"

void Sound_ping(void) {
    switch(GetRandomValue(0, 4)) {
        case 0:
            PlaySound(fx_ping_1);
            break;
        case 1:
            PlaySound(fx_ping_2);
            break;
        case 2:
            PlaySound(fx_ping_3);
            break;
        case 3:
            PlaySound(fx_ping_4);
            break;
        case 4:
            PlaySound(fx_ping_5);
            break;
        default:
            break;
    }
}

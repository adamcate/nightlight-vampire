#include "game.h"

surface_t* display;

int render()
{
    surface_t *disp = display_lock();
    if(!disp) return;

    rdp_attach(disp);


    switch(state)
    {
        case STATE_READY:
            break;
        case STATE_MENU:
            break;
        case STATE_GAMEOVER:
            break;
        case STATE_INTRO:
            break;
        case STATE_GAME:
            for(int i = )
            break;
        default:
            break;
    }
}
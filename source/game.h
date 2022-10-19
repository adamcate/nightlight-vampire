#ifndef GAME_H
#define GAME_H

#include "assets.h"
#include "controller.h"
#include "render.h"
#include "libdragon.h"
#include <stdbool.h>
#include <stdint.h>

void update_audio();
void game_tick();

typedef enum{
    STATE_MENU = 0,
    STATE_READY = 1,
    STATE_INTRO = 2,
    STATE_GAMEOVER = 3,
    STATE_GAME = 4
}game_state_t;

typedef struct{
    int col_index;
    bool isLight;
}game_tile_t;


extern uint16_t score;
extern uint16_t level_no;

extern game_state_t state;

extern uint32_t player_x;
extern uint32_t player_y;

extern uint8_t cell_x;
extern uint8_t cell_y;

extern uint8_t lives;

extern surface_t* display;
extern surface_t bk_surf;

#endif
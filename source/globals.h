#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <stdbool.h>

#include "libdragon.h"


typedef enum
{
    
    STATE_GAME = 0,
    STATE_READY = 1,
    STATE_MENU = 2,
    STATE_GAMEOVER = 3,
    STATE_INTRO = 4

}game_state_t;

typedef struct
{

    uint8_t col_index : 4;
    uint8_t is_lit : 2;
    bool warning_flash : 1;

}game_block;


extern game_state_t game_state;
extern uint32_t player_x;
extern uint32_t player_y;

extern uint8_t cell_x;
extern uint8_t cell_y;


extern sprite_t* block_sprite;
extern sprite_t* block_palette;

extern surface_t block_surf;
// extern surface_t block_palette_surf;

extern sprite_t* player_sprite;
extern surface_t player_surf;

#endif
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
    bool is_occupied : 1;

}game_block;

void render_background();
extern game_block gamefield[7][7];

extern const game_block block_empty;
extern const game_block block_full;

extern game_state_t game_state;

extern int anim_frame;
extern uint32_t player_x;
extern uint32_t player_y;

extern int cell_x;
extern int cell_y;

extern uint32_t level;


extern sprite_t* block_sprite;
extern sprite_t* block_palette;

extern surface_t block_surf;


extern sprite_t* player_sprite;
extern surface_t player_surf;

extern sprite_t* playfield_background;

extern sprite_t* scoreboard;
extern surface_t scoreboard_surf;

extern bool dir_held[4];

#endif
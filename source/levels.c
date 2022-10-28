  #include "globals.h"
  #include "libdragon.h"

game_block gamefield[7][7];

const game_block block_empty = {
    .col_index = 0,
    .is_lit = 0,
    .is_occupied = false,
    .warning_flash = 0
};

const game_block block_full = {
    .col_index = 0,
    .is_lit = 0,
    .is_occupied = true,
    .warning_flash = 0
};
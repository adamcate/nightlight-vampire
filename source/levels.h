#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

#include <stdint.h>


#define LEVEL_WIDTH  4
#define LEVEL_HEIGHT 4
#define NUM_LEVELS   2
#define NUM_TILES    2

typedef struct{
    uint8_t tile_page       : 4;
    uint8_t tile_index      : 4;
    uint8_t light_level     : 1;
    uint8_t tile_behavior   : 5;
    uint8_t tile_state      : 2;
}level_tile_t;

typedef struct{
    char* name;
    level_tile_t tiles[LEVEL_WIDTH*LEVEL_HEIGHT];
    int trackno;
}level_t;

extern level_tile_t tile_types[NUM_TILES];
extern level_t* current_level;
extern level_t level_list[NUM_LEVELS];

#endif
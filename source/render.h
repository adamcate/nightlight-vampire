#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include <stdbool.h>

#define SCREEN_TILES_X  21
#define SCREEN_TILES_Y  16


void draw_background(int32_t scroll_x, int32_t scroll_y);
void draw_character(uint32_t screen_x, uint32_t screen_y);
void update_tilemap_lights();

#endif
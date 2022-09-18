#include "tilemap.h"
#include "render.h"
#include "assets.h"
#include "libdragon.h"


tile level_map[LEVEL_MAX_WIDTH][LEVEL_MAX_HEIGHT];

static surface_t surface_bk_tile_page;

void draw_background(int32_t scroll_x, int32_t scroll_y){
    
    rdpq_set_mode_copy(true);
    rdpq_mode_tlut(TLUT_RGBA16);

    rdpq_tex_load_tlut(sprite_get_palette(bk_tileset[0]),0,256);

    for(int page = 0; page < 4; ++page){
        surface_bk_tile_page = sprite_get_pixels(bk_tileset[page]);
        for(int descriptor_index = 0; descriptor_index < 8; ++descriptor_index){
            
        }
        
        for(int y = 0; y < SCREEN_TILES_Y; ++y){
            for(int x = 0; x < SCREEN_TILES_X; ++x){
            }
        }
    }

    rdpq_mode_tlut(TLUT_NONE);
}

void draw_character(uint32_t screen_x, uint32_t screen_y);
void update_tilemap_lights();
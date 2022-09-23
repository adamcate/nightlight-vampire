#include "libdragon.h"
#include "assets.h"
//#include "controller.h"
#include "render.h"
#include "tilemap.h"

#include <malloc.h>


static tile template = 0;

static int scroll_x = 0, scroll_y = 0;


// pointers to the sprites for all bk tiles
sprite_t* bk_tileset[BK_TILE_PAGES];

// pointers to the sprites for all entity tiles
sprite_t* entity_tileset[ENTITY_PAGES];

// xm format music player
xm64player_t music_player;

// actively loaded sound effect
wav64_t sound_effect;

void load_sprites(){
    for(int page = 0; page < BK_TILE_PAGES; ++page){
        bk_tileset[page] = sprite_load(bk_tileset_names[page]);
    }
    for(int page = 0; page < ENTITY_PAGES; ++page){
        entity_tileset[page] = sprite_load(entity_tileset_names[page]);
    }
}

void init_background(){

    T_SET_INDEX(template,0);
    T_SET_PG(template,0);
    T_SET_PALETTE(template,0);
    T_SET_TYPE(template,0);
    T_SET_MIRROR(template,0);

    for(int i = 0; i < LEVEL_MAX_WIDTH; ++i){
        for(int j = 0; j < LEVEL_MAX_HEIGHT; ++j){
            level_map[i][j] = template;
        }
    }
}

void draw_frame(){
    surface_t* display = display_lock();
    if(!display) return;

    //player_get_buttons();

    draw_background(scroll_x,scroll_y);
}

int main()
{
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_RESAMPLE);

    debug_init_isviewer();
    debug_init_usblog();

    controller_init();
    timer_init();
    
    dfs_init(DFS_DEFAULT_LOCATION);

    load_sprites();

    audio_init(44100, 4);
    mixer_init(32);

    rdp_init();
    rdpq_debug_start();

    rdpq_mode_antialias(false);

    while(1){
        draw_frame();
    }
}
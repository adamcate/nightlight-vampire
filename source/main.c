#include "libdragon.h"
#include <malloc.h>


static xm64player_t xm;

static sprite_t *tiles_sprite;

// static rspq_block_t *tiles_block;
surface_t tiles_surf;

static uint32_t bk_x = 0;
// static uint32_t bk_y = 0;

static struct controller_data c_keys;

void render()
{
    surface_t *disp = display_lock();
    if (!disp)
    {
        return;
    }

    /*bk_x += 1;

    if(bk_x >= 240) bk_x = 0;
    */
    rdp_attach(disp);
    
    rdpq_set_mode_copy(true);
    

    rdpq_mode_tlut(TLUT_RGBA16);
    rdpq_tex_load_tlut(sprite_get_palette(tiles_sprite), 0, 16);
    uint32_t tile_width = 16;
    uint32_t tile_height = 16;

    int s = 0, t = 0;
    

    for (uint32_t ty = 0; ty < 240; ty += tile_height)
    {
        for (int32_t tx = -8; tx < 320; tx += tile_width)
        {
            
            rdpq_texture_rectangle(TILE0, tx, ty, tx+16, ty+16, s, t, 1, 1);
        }
    }

    rdpq_mode_tlut(TLUT_NONE);    

    rdp_detach_show(disp);

}

int main()
{
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_RESAMPLE);

    debug_init_isviewer();
    debug_init_usblog();

    controller_init();
    timer_init();
    
    dfs_init(DFS_DEFAULT_LOCATION);

    audio_init(44100, 4);
    mixer_init(32);

    rdp_init();
    rdpq_debug_start();

    rdpq_mode_antialias(false);


    tiles_sprite = sprite_load("rom:/tiles.sprite");

    tiles_surf = sprite_get_pixels(tiles_sprite);

    

    xm64player_open(&xm, "rom:/Caverns16bit.xm64");
    xm64player_play(&xm, 2);
    rdpq_tex_load_sub(TILE0, &tiles_surf, 0, 0, 0, 16, 16);

    while (1)
    {
        
        controller_scan();

        c_keys = get_keys_down();

        if (c_keys.c[0].C_up) {
            bk_x += 5;
        }

        if (c_keys.c[0].C_down) {
            bk_x -= 5;
        }
        render();
        
        if (audio_can_write()) {    	
            short *buf = audio_write_begin();
            mixer_poll(buf, audio_get_buffer_length());
            audio_write_end();
        }
    }
}
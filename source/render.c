#include "render.h"
#include "globals.h"

#include "libdragon.h"
#include <malloc.h>


static uint32_t offset_x = 48;
static const uint32_t offset_y = 200;

static int frame_counter = 0;
static int palette_counter = 0;

static volatile color_t bk_color = {
    .r = 0,
    .b = 0,
    .g = 0,
    .a = 255
};

void render_background(){
    surface_t bk_surf = sprite_get_pixels(playfield_background);

    rdpq_set_mode_copy(true);
    rdpq_mode_tlut(TLUT_NONE);
    
    for(int x = 0; x <= 280; x+=40){
        for(int y = 0; y <= 200; y+=40){
            rdpq_tex_load_sub(TILE0, &bk_surf, 0, x, y, x+40,y+40);
            rdpq_texture_rectangle(TILE0,x,y,x+40,y+40,x,y,1,1);
        }
    }

    rdpq_tex_load_sub_ci4(TILE0,&scoreboard_surf,0,0,0,0,128,64);
    rdpq_texture_rectangle(TILE0,0,0,128,64,0,0,1,1);
    /*rdpq_tex_load_sub_ci4(TILE0,&scoreboard_surf,0,0,64,0,128,64);
    rdpq_texture_rectangle(TILE0,64,0,128,64,64,0,1,1);*/


}

void render_playfield(){
    rdpq_set_mode_copy(true);
    rdpq_mode_antialias(false);

    rdpq_mode_tlut(TLUT_RGBA16);
    rdpq_tex_load_tlut(sprite_get_palette(block_palette), 0, 256);

    rdpq_tex_load_sub_ci4(TILE0,&block_surf, 0, palette_counter, 0, 0, 32, 32);

    int offset_row = 0;

    for(int i = 0; i < 7; ++i)
    {
        for(int j = 0; j < 7 - offset_row; ++j)
        {
            rdpq_texture_rectangle(TILE0,32*i+offset_x,offset_y-24*j,32+32*i+offset_x,32+offset_y-24*j,0,0,1,1);
            offset_x += 16;
        }
        offset_x = 48;
        ++offset_row;
    }


    rdpq_mode_tlut(TLUT_NONE);
}

void render_game(){
    surface_t* disp = display_lock();

    if(!disp) return;

    frame_counter++;
    frame_counter %= 4;

    if(frame_counter == 0) palette_counter++;
    if(palette_counter > 6) palette_counter = 0;


    rdp_attach(disp);

    render_background();

    render_playfield();

    
    
    rdp_detach_show(disp);

}
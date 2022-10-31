#include "render.h"
#include "globals.h"
#include "game.h"

#include "libdragon.h"
#include <malloc.h>


const int playfield_x = 48;
const int playfield_y = 200;
static int frame_counter = 0;
static int palette_counter = 0;

int anim_frame = 0;

static volatile color_t bk_color = {
    .r = 0,
    .b = 0,
    .g = 0,
    .a = 255
};


void render_player(){
    rdpq_set_mode_copy(true);
    rdpq_mode_tlut(TLUT_RGBA16);
    rdpq_mode_antialias(false);

    rdpq_tex_load_tlut(sprite_get_palette(player_sprite),0,16);
    rdpq_tex_load_sub_ci4(TILE0,&player_surf,0,0,anim_frame*32,0,32+anim_frame*32,32);
    rdpq_texture_rectangle(TILE0,player_x,player_y,player_x+32,player_y+32,anim_frame*32,0,1,1);

    rdpq_mode_tlut(TLUT_NONE);
}


void render_background(){
    surface_t bk_surf = sprite_get_pixels(playfield_background);

    rdpq_set_mode_copy(true);
    //rdpq_set_mode_standard();
    rdpq_mode_tlut(TLUT_NONE);
    rdpq_mode_antialias(false);

    for(int x = 0; x <= 280; x+=40){
        for(int y = 0; y <= 200; y+=40){
            rdpq_tex_load_sub(TILE0, &bk_surf, 0, x, y, x+40,y+40);
            rdpq_texture_rectangle(TILE0,x,y,x+40,y+40,x,y,1,1);
        }
    }
}


void render_playfield(){
    rdpq_set_mode_copy(true);
    rdpq_mode_antialias(false);

    rdpq_tex_load_sub(TILE0,&scoreboard_surf,0,0,0,64,32);
    rdpq_texture_rectangle(TILE0,200,15,200+64,15+32,0,0,1,1);

    rdpq_mode_tlut(TLUT_RGBA16);
    rdpq_tex_load_tlut(sprite_get_palette(block_palette), 0, 256);

    rdpq_tex_load_sub_ci4(TILE0,&block_surf, 0, 0, 0, 0, 32, 32);
    rdpq_texture_rectangle(TILE0,270,15,302,47,0,0,1,1);
    for(int i = 0; i < 7; ++i)
    {

        for(int palette = 0; palette < 5; ++palette)
        {
            int grid_y = 7 - i - 1;
            int grid_x = 0;

            rdpq_tex_load_sub_ci4(TILE0,&block_surf, 0, palette, 0, 0, 32, 32);
            
            for(int j = 0; j < 7 - i; ++j)
            {
                if(gamefield[grid_x][grid_y].col_index == palette)
                {
                    rdpq_texture_rectangle(TILE0,playfield_x + 32*j+16*i,playfield_y-24*i,playfield_x + 32+32*j+16*i,32+playfield_y-24*i,0,0,1,1);
                }
                grid_x++;
                grid_y--;

            }
        }
    }


    rdpq_mode_tlut(TLUT_NONE);
}


void render_game(){
    surface_t* disp = display_lock();

    if(!disp) return;

    get_controller_inputs(dir_held);

    frame_counter++;
    frame_counter %= 4;

    if(frame_counter == 0) palette_counter++;
    if(palette_counter > 6) palette_counter = 0;


    rdp_attach(disp);

    render_background();

    render_playfield();

    render_player();
    
    
    rdp_detach_show(disp);
    // for(int i = 0; i < cell_x; ++i) graphics_draw_text(disp, i * 5 + 15, 15, "*");
    // for(int i = 0; i < cell_y; ++i) graphics_draw_text(disp, i * 5 + 15, 30, "*");
}
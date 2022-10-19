#include "game.h"

surface_t* display;
surface_t bk_surf;
surface_t block_surf;

static color_t bk_color = {
    .r = 0,
    .g = 0,
    .b = 0,
    .a = 255
};

int render()
{
    surface_t *disp = display_lock();
    if(!disp) return -1;

    rdp_attach(disp);


    switch(state)
    {
        case STATE_READY:
            break;
        case STATE_MENU:
            rdpq_set_mode_copy(true);
            for(int tilex = 0; tilex < 8; ++tilex)
            {
                for(int tiley = 0; tiley < 6; ++tiley)
                {
                    rdpq_tex_load_sub(TILE0,&bk_surf,0,tilex*40,tiley*40,tilex*40+40,tiley*40+40);
                    rdpq_texture_rectangle(TILE0,tilex*40,tiley*40,tilex*40+40,tiley*40+40,0,0,1,1);
                }
            }
            break;
        case STATE_GAMEOVER:
            break;
        case STATE_INTRO:
            break;
        case STATE_GAME:
            rdpq_set_mode_fill(bk_color);
            rdpq_fill_rectangle(0,0,320,240);

            rdpq_set_mode_copy(true);
            rdpq_mode_tlut(TLUT_RGBA16);

            rdpq_load_tlut(sprite_get_palette(block_palette),0,255);

            // draw gamefield here

            rdpq_set_mode_standard();   // must be set to standard due to flip not being possible in copy mode

            rdpq_mode_tlut(TLUT_NONE);

            rdpq_tex_load(TILE0, &player_surf, 0);

            // draw player here

            // now draw scoreboard info


            break;
        default:
            break;
    }
    return 0;
}
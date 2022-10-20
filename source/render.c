#include "render.h"
#include "globals.h"

#include "libdragon.h"


static color_t bk_color = {
    .r = 0,
    .b = 0,
    .g = 0,
    .a = 255
};

void render_game(){
    surface_t* disp = display_lock();
    if(!disp) return;

    rdp_attach(disp);

    rdpq_set_mode_fill(bk_color);
    rdpq_fill_rectangle(0,0,320,240);


    rdpq_set_mode_copy(true);
    rdpq_mode_antialias(false);

    rdpq_mode_tlut(TLUT_RGBA16);
    rdpq_tex_load_tlut(sprite_get_palette(block_palette), 0, 256);

    rdpq_tex_load_sub_ci4(TILE0,&block_surf, 0, 0, 0, 0, 32, 32);
    rdpq_texture_rectangle(TILE0,0,0,32,32,0,0,1,1);


    rdpq_mode_tlut(TLUT_NONE);

    rdp_detach_show(disp);
}
#include "libdragon.h"
#include <malloc.h>
#include <stdbool.h>

static int dpad[4] = {0,0,0,0};

const int speed = 5;

static sprite_t* bk_tiles;
static sprite_t* bk_palette;
static sprite_t* character_sprite;

static xm64player_t xm;

surface_t tiles_surf;
surface_t char_surf;

int alt = 0;
static int char_x = 0;
static int char_y = 0;

typedef struct{
    int index;
    int palette;
}bk_t;


int bk[4][16] ={
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}
};


void render(){
    surface_t* disp = display_lock();
    if(!disp) return;
    
    rdp_attach(disp);

    rdpq_set_mode_copy(true);
    rdpq_mode_tlut(TLUT_RGBA16);
    char_y += (dpad[0] + dpad[1]) * speed;
    char_x += (dpad[2] + dpad[3]) * speed;    

    rdpq_tex_load_tlut(sprite_get_palette(bk_palette),0,32);
    rdpq_tex_load_sub_ci4(TILE0, &tiles_surf, 0, 0, 0, 0, 64, 64);
    for(int p = 0; p<2; ++p){
        rdpq_tex_load_sub_ci4(TILE0, &tiles_surf, 0, p, 0, 0, 64, 64);
        for(int index = 0; index < 16; ++index){
            for(int x = 0; x < 16; ++x){
                for(int y = 0; y < 16; ++y){
                    if(bk[y % 4][x] == index && (index + p ) % 2){
                        rdpq_texture_rectangle(TILE0, x * 16, y * 16, x * 16+16, y * 16+16, (index % 4) * 16, (int)(index / 4) * 16, 1.f, 1.f);
                    }
                }
            }
        }
    }

    rdpq_tex_load_sub_ci4(TILE0, &char_surf, 0, 0,0,0,16,32);
    rdpq_texture_rectangle(TILE0,char_x,char_y,char_x+16,char_y+32,0,0,1.f,1.f);

    rdp_detach_show(disp);
}
int main(){
    display_init(RESOLUTION_320x240,DEPTH_16_BPP,3,GAMMA_NONE,ANTIALIAS_RESAMPLE);

    debug_init_isviewer();
    debug_init_usblog();

    controller_init();
    timer_init();

    dfs_init(DFS_DEFAULT_LOCATION);

    audio_init(44100, 2);
    mixer_init(32);


    rdp_init();
    rdpq_debug_start();

    rdpq_mode_begin();
    rdpq_mode_antialias(false);
    rdpq_mode_end();

    bk_tiles = sprite_load("rom:/bk_tiles_1.sprite");
    bk_palette = sprite_load("rom:/p2.sprite");
    character_sprite = sprite_load("rom:/fanger.sprite");

    tiles_surf = sprite_get_pixels(bk_tiles);
    char_surf  = sprite_get_pixels(character_sprite);
    xm64player_open(&xm, "rom:/intro2.xm64");
    xm64player_play(&xm, 0);

    while(1){
        controller_scan();
        struct controller_data ckeys = get_keys_pressed();

        for(int i = 0; i < 4; ++i){dpad[i] = 0;}

        

        if(ckeys.c[0].up){
            dpad[0] = -1;
        }
        if(ckeys.c[0].down){
            dpad[1] = 1;
        }
        if(ckeys.c[0].left){
            dpad[2] = -1;
        }
        if(ckeys.c[0].right){
            dpad[3] = 1;
        }
        render();
        if (audio_can_write()) {    	
            short *buf = audio_write_begin();
            mixer_poll(buf, audio_get_buffer_length());
            audio_write_end();
        }
        
        
    }

    return 0;
}
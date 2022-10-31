#include <stdint.h>
#include <malloc.h>

#include "libdragon.h"
#include "globals.h"
#include "render.h"
#include "game.h"

int f_stage = 0;

game_state_t game_state = STATE_MENU;

bool flashing_state = false;

uint32_t player_x = 40;
uint32_t player_y = 40;

const int cell_x_init = 0;
const int cell_y_init = 0;

int cell_x = cell_x_init;
int cell_y = cell_y_init;

uint32_t level = 1;
int32_t lives = 3;

const uint32_t init_timer_val  = SECONDS_TO_FRAMES(5);

uint32_t perm_timer = init_timer_val;
uint32_t frame_timer = 0;
uint32_t curr_diff_timer = init_timer_val;

sprite_t* block_sprite;
sprite_t* block_palette;

surface_t block_surf;

sprite_t* player_sprite;

surface_t player_surf;

sprite_t* playfield_background;

sprite_t* scoreboard;
surface_t scoreboard_surf;

sprite_t* gameover_sprite;

static xm64player_t xm;

bool dir_held[4] = {false, false, false, false};

int main()
{
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_RESAMPLE);

    dfs_init(DFS_DEFAULT_LOCATION);


    audio_init(41000,2);
    mixer_init(32);
    controller_init();

    rdp_init();
    rdpq_debug_start();

    gameover_sprite = sprite_load("rom:/game_over.sprite");

    while(1)
    {

        playfield_background = sprite_load("rom:/TITLE.sprite");
        
        while(game_state == STATE_MENU){
            controller_scan();
            struct controller_data control = get_keys_down();

            if(control.c[0].start) game_state = STATE_GAME;

            surface_t* disp = display_lock();
            if(!disp) continue;

            rdp_attach(disp);

            render_background();
            
            rdp_detach_show(disp);
        }
        
        sprite_free(playfield_background);

        block_sprite = sprite_load("rom:/block.sprite");
        block_palette = sprite_load("rom:/block_palette.sprite");
        player_sprite = sprite_load("rom:/player_sprite.sprite");
        scoreboard = sprite_load("rom:/scoreboard.sprite");

        block_surf = sprite_get_pixels(block_sprite);
        player_surf = sprite_get_pixels(player_sprite);
        scoreboard_surf = sprite_get_pixels(scoreboard);


        xm64player_open(&xm, "rom:/3_OldLonely.xm64");
        xm64player_play(&xm, 0);

        
        init_gamefield();
        
        playfield_background = sprite_load("rom:/playfield_background.sprite");
        while(game_state == STATE_GAME)
        {
            render_game();

            if(frame_timer >= curr_diff_timer){
                switch(f_stage)
                {
                    case 0:
                        flashing_state = true;
                        for(int i = 5; i >= 1; --i){
                            for(int x = 1; x < 6-i; ++x){
                                gamefield[i][x].is_lit = true;
                            }
                        }
                        curr_diff_timer /= 4;
                        f_stage++;
                        break;
                    case 1:
                        flashing_state = false;
                        
                        f_stage++;
                        break;
                    case 2:
                        curr_diff_timer *=4;
                        for(int i = 5; i >= 0; --i){
                            for(int x = 0; x < 6-i; ++x){
                                gamefield[i][x].is_lit = false;
                            }
                        }
                        f_stage = 0;
                        break;
                    default:
                        break;
                }
                frame_timer = 0;
            }

            if (audio_can_write()) 
            {    	
                short *buf = audio_write_begin();
                mixer_poll(buf, audio_get_buffer_length());
                audio_write_end();
            }

            if(test_win_condition(level)){
                curr_diff_timer = perm_timer;

                if (curr_diff_timer > SECONDS_TO_FRAMES(2)) curr_diff_timer -= 30;
                perm_timer = curr_diff_timer;
                
                frame_timer = 0;
                player_x = 40;
                player_y = 40;

                cell_x = 0;
                cell_y = 0;

                init_gamefield();

                anim_frame = 0;

                level++;
                if(lives < 4) lives++;
            }
            
            if(!flashing_state && gamefield[cell_x][cell_y].is_lit){
                curr_diff_timer = perm_timer;
                frame_timer = 0;
                player_x = 40;
                player_y = 40;

                cell_x = 0;
                cell_y = 0;

                anim_frame = 0;
                lives--;

                for(int i = 5; i >= 0; --i){
                    for(int x = 0; x < 6-i; ++x){
                        gamefield[i][x].is_lit = false;
                    }
                }

                f_stage = 0;
                flashing_state = false;
            }

            if(lives < 0){
                int gameovertimer = 0;
                while(gameovertimer < SECONDS_TO_FRAMES(5)){
                    surface_t* disp = display_lock();
                    if(!(disp)) continue;

                    rdp_attach(disp);

                    rdpq_set_mode_copy(true);

                    surface_t go_surf = sprite_get_pixels(gameover_sprite);
                    rdpq_tex_load_sub(TILE0,&go_surf,0,0,0,128,16);
                    rdpq_texture_rectangle(TILE0,32,56,32+256,56+32,0,0,0.5,0.5);

                    rdp_detach_show(disp);
                    gameovertimer++;
                }
                f_stage = 0;
                frame_timer = 0;
                lives = 3;

                player_x = 40;
                player_y = 40;

                cell_x = 0;
                cell_y = 0;

                init_gamefield();

                anim_frame = 0;

                level = 1;
                game_state = STATE_MENU;
            }
        }

        f_stage = 0;

        flashing_state = false;

        curr_diff_timer = init_timer_val;
        perm_timer = curr_diff_timer;

        sprite_free(block_sprite);
        sprite_free(block_palette);
        sprite_free(player_sprite);

        xm64player_close(&xm);
    }
    return 0;
}
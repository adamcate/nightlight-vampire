#include <stdint.h>
#include <malloc.h>

#include "libdragon.h"
#include "globals.h"
#include "render.h"
#include "game.h"


game_state_t game_state = STATE_GAME;

uint32_t player_x = 40;
uint32_t player_y = 40;

const int cell_x_init = 0;
const int cell_y_init = 0;

int cell_x = cell_x_init;
int cell_y = cell_y_init;

uint32_t score = 20;


sprite_t* block_sprite;
sprite_t* block_palette;

surface_t block_surf;

sprite_t* player_sprite;

surface_t player_surf;

sprite_t* playfield_background;

sprite_t* scoreboard;
surface_t scoreboard_surf;

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

    while(1)
    {

        block_sprite = sprite_load("rom:/block.sprite");
        block_palette = sprite_load("rom:/block_palette.sprite");
        player_sprite = sprite_load("rom:/player_sprite.sprite");
        playfield_background = sprite_load("rom:/playfield_background.sprite");
        scoreboard = sprite_load("rom:/scoreboard.sprite");

        block_surf = sprite_get_pixels(block_sprite);
        player_surf = sprite_get_pixels(player_sprite);
        scoreboard_surf = sprite_get_pixels(scoreboard);

        xm64player_open(&xm, "rom:/3_OldLonely.xm64");
        xm64player_play(&xm, 0);

        init_gamefield();
        
        while(game_state == STATE_GAME)
        {
            render_game();

            if (audio_can_write()) {    	
            short *buf = audio_write_begin();
            mixer_poll(buf, audio_get_buffer_length());
            audio_write_end();
        }
        }

        sprite_free(block_sprite);
        sprite_free(block_palette);
        sprite_free(player_sprite);
    }
    return 0;
}
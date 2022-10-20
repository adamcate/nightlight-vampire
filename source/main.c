#include <stdint.h>
#include <malloc.h>

#include "libdragon.h"
#include "globals.h"
#include "render.h"


game_state_t game_state = STATE_GAME;

uint32_t player_x = 0;
uint32_t player_y = 0;

uint8_t cell_x = 0;
uint8_t cell_y = 0;


sprite_t* block_sprite;
sprite_t* block_palette;

surface_t block_surf;
// surface_t block_palette_surf;

sprite_t* player_sprite;

surface_t player_surf;


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

        block_surf = sprite_get_pixels(block_sprite);
        player_surf = sprite_get_pixels(player_sprite);


        while(game_state == STATE_GAME)
        {
            render_game();
        }

        sprite_free(block_sprite);
        sprite_free(block_palette);
        sprite_free(player_sprite);
    }
    return 0;
}
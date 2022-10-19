#include <stdint.h>
#include <malloc.h>

#include "libdragon.h"

#include "game.h"


const uint8_t starting_lives = 3;

uint16_t score = 0;
uint16_t level_no = 1;

uint32_t player_x = 0;
uint32_t player_y = 0;

uint8_t cell_x = 0;
uint8_t cell_y = 0;

uint8_t lives = starting_lives;

void game_tick(){
    if(render() == -1) return;

    controller_scan();
    struct controller_data ckeys = get_keys_down();
    get_input(&ckeys);
}

int main()
{
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_RESAMPLE);

    dfs_init(DFS_DEFAULT_LOCATION);


    audio_init(41000,2);
    controller_init();

    rdp_init();
    rdpq_debug_start();

    while(1)
    {
        title_background = sprite_load("rom:/title_background.sprite");

        while(state == STATE_MENU)
        {

            render();
            update_audio();
        }

        sprite_free(title_background);

        block_sprite = sprite_load("rom:/block.sprite");
        block_palette = sprite_load("rom:/block_palette.sprite");
        player_sprite = sprite_load("rom:/player_sprite.sprite");

        while(state != STATE_GAMEOVER)
        {
            game_tick();

            update_audio();
        }

        sprite_free(block_sprite);
        sprite_free(block_palette);
        sprite_free(player_sprite);
    }
    return 0;
}
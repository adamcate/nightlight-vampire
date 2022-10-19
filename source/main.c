#include <stdint.h>
#include <malloc.h>

#include "libdragon.h"

#include "game.h"

int score;
game_state_t state;


int main(){
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_RESAMPLE);

    dfs_init(DFS_DEFAULT_LOCATION);

    block_sprite = sprite_load("rom:/block.sprite");
    block_palette = sprite_load("rom:/block_palette.sprite");

    audio_init(41000,2);
    controller_init();

    rdp_init();
    rdpq_debug_start();


    while(1){
        if
        printf("hello");
    }
    return 0;
}
#include "globals.h"
#include "controller.h"

#include "libdragon.h"

void init_gamefield(){
    for(int x = 0; x < 7; ++x){
        for(int y = 0; y < 7; ++y){
            gamefield[y][x] = block_empty;
        }
    }

    for(int i = 6; i >= 0; --i){
        for(int x = 0; x < 7-i; ++x){
            gamefield[i][x] = block_full;
        }
    }
}

bool test_win_condition(int col_index){
    int count = 0;
    count++;
    return true;
}

void get_controller_inputs(bool* outputs)
{
    controller_scan();
    struct controller_data dpad_down = get_keys_down();

    for(int i = 0; i < 4; ++i) dir_held[i] = false;

    if(dpad_down.c[0].up){
        anim_frame = 7;
        dir_held[0] = true;
        if(!(cell_x+cell_y > 6)) cell_y--;
    }
    if(dpad_down.c[0].down){
        if(!(cell_x+cell_y >= 6)) cell_y++;
        anim_frame = 0;
        dir_held[1] = true;
    }
    if(dpad_down.c[0].left){
        if(!(cell_x+cell_y > 6)) cell_x--;
        anim_frame = 2;
        dir_held[2] = true;
    }
    if(dpad_down.c[0].right){
        if(!(cell_x+cell_y >= 6)) cell_x++;
        anim_frame = 4;
        dir_held[3] = true;           
    }
    if(cell_x < 0) cell_x = 0;
    if(cell_y < 0) cell_y = 0;

    player_y = (cell_x + cell_y) * 24 + 32;
    player_x = (cell_x - cell_y)*16 + 144;

    bool getInput = false;
    for(int i = 0; i < 4; ++i){
        if(dir_held[i]){
            getInput = true;
            break;
        }
    }
    if(!getInput) return;

    gamefield[cell_x][cell_y].col_index += 1;
    gamefield[cell_x][cell_y].col_index %= (level + 1);

    if(dpad_down.c[0].A){gamefield[cell_x][cell_y].is_lit = true;}
}
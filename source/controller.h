#ifndef CONTROLLER_H
#define CONTROLLER_H


typedef enum{
    C_GAME,
    C_CUTSCENE,
    C_MENU
}controller_state;

void player_get_buttons();

#endif
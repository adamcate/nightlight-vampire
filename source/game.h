#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

void get_controller_inputs(bool* outputs);
void init_gamefield();
bool test_win_condition(int col_index);

#endif
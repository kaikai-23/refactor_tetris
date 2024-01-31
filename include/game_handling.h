#ifndef GAME_HANDLING_H
#define GAME_HANDLING_H

#include "tetris.h"

void handle_key_input(game_information *info_ptr, int pressed_key);
void handle_free_fall(game_information *info_ptr);

#endif

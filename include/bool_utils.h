#ifndef BOOL_UTILS_H
#define BOOL_UTILS_H

#include "tetris.h"

bool is_outside_of_board(const block_data block, const int i, const int j);
bool is_block_position_occupied(const block_data block, const int i, const int j, const char game_board[BOARD_ROWS][BOARD_COLS]);
bool is_block_position_valid(const block_data block, const char game_board[BOARD_ROWS][BOARD_COLS]);
bool should_update_block(const game_time_data time_data);

#endif

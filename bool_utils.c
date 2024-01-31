#include "tetris.h"

bool is_outside_of_board(const block_data block, const int i, const int j)
{
	return (block.position_col + j < 0 || block.position_col + j >= BOARD_COLS || block.position_row + i >= BOARD_ROWS);
}

bool is_block_position_occupied(const block_data block, const int i, const int j, const char game_board[BOARD_ROWS][BOARD_COLS])
{
	return (game_board[block.position_row + i][block.position_col + j]);
}

bool is_block_position_valid(const block_data block, const char game_board[BOARD_ROWS][BOARD_COLS])
{
	for (int i = 0; i < block.block_width; i++) {
		for (int j = 0; j < block.block_width ; j++){
			if (block.block_matrix[i][j])
			{
				if (is_outside_of_board(block, i, j) || is_block_position_occupied(block, i, j, game_board))
					return FALSE;
			}
		}
	}
	return TRUE;
}

bool should_update_block(const game_time_data time_data)
{
	suseconds_t current_time, previous_time;

	current_time = time_data.now.tv_sec * MICROSECONDS_PER_SECOND + time_data.now.tv_usec;
	previous_time = time_data.before_now.tv_sec * MICROSECONDS_PER_SECOND + time_data.before_now.tv_usec;

	return (current_time - previous_time > time_data.interval_time);
}

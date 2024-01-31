#include "../include/tetris.h"

void initialize_game_information(game_information *info_ptr)
{
	info_ptr->score = FIRST_SCORE;

	info_ptr->current_block = create_new_block();

	for (int x = 0; x < BOARD_ROWS; x++)
		for (int y = 0; y < BOARD_COLS; y++)
			info_ptr->game_board[x][y] = 0;

	info_ptr->is_game_active = is_block_position_valid(info_ptr->current_block, info_ptr->game_board);

	info_ptr->game_time.interval_time = INTERVAL_TIME;
	info_ptr->game_time.drop_speed_up = DROP_SPEED_UP;
	gettimeofday(&info_ptr->game_time.before_now, NULL);
	gettimeofday(&info_ptr->game_time.now, NULL);
}

void initialize_random_generator()
{
	srand(CURRENT_TIME);
}

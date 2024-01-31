#include "test.h"

static void _move_block_down(game_information *info_ptr)
{
	block_data temp = copy_block(info_ptr->current_block);
	temp.position_row++;
    if (is_block_position_valid(temp, info_ptr->game_board))
        info_ptr->current_block.position_row++;
    else
        update_game_after_block_fix(info_ptr);
    free_block_memory(&temp);
}

static void _move_block_right(game_information *info_ptr)
{
    block_data temp = copy_block(info_ptr->current_block);
    temp.position_col++;
    if (is_block_position_valid(temp, info_ptr->game_board))
        info_ptr->current_block.position_col++;
    free_block_memory(&temp);
}

static void _move_block_left(game_information *info_ptr)
{
    block_data temp = copy_block(info_ptr->current_block);
    temp.position_col--;
    if (is_block_position_valid(temp, info_ptr->game_board))
        info_ptr->current_block.position_col--;
    free_block_memory(&temp);
}

/*
90度時計回りに回転
例えば、
1 2 3      7 4 1
4 5 6  =>  8 5 2
7 8 9      9 6 3
*/
void _rotate_block(block_data block){
	block_data temp = copy_block(block);
	int width = block.block_width;

	for(int i = 0; i < width ; i++)
	{
		for(int j = 0, k = width - 1; j < width ; j++, k--)
				block.block_matrix[i][j] = temp.block_matrix[k][i];
	}
	free_block_memory(&temp);
}

static void _move_block_rotate(game_information *info_ptr)
{
    block_data temp = copy_block(info_ptr->current_block);
	_rotate_block(temp);
	if (is_block_position_valid(temp, info_ptr->game_board))
		_rotate_block(info_ptr->current_block);
	free_block_memory(&temp);
}

void handle_free_fall(game_information *info_ptr)
{
	gettimeofday(&info_ptr->game_time.now, NULL);
	if (should_update_block(info_ptr->game_time))
	{
		_move_block_down(info_ptr);
		gettimeofday(&info_ptr->game_time.before_now, NULL);
	}
}

void handle_key_input(game_information *info_ptr, int pressed_key)
{
	switch (pressed_key)
	{
	case DOWN_KEY:
		_move_block_down(info_ptr);
		break;
	case RIGHT_KEY:
		_move_block_right(info_ptr);
		break;
	case LEFT_KEY:
		_move_block_left(info_ptr);
		break;
	case ROTATE_KEY:
		_move_block_rotate(info_ptr);
		break;
	}
}

#include "../include/tetris.h"

static void _fix_block(const block_data block, char game_board[BOARD_ROWS][BOARD_COLS])
{
	for (int i = 0; i < block.block_width; i++)
	{
		for (int j = 0; j < block.block_width; j++)
		{
			if(block.block_matrix[i][j])
				game_board[block.position_row + i][block.position_col + j] = block.block_matrix[i][j];
		}
	}
}

static bool _is_oneline_filled(const char game_board[BOARD_COLS])
{
	for (int x = 0; x < BOARD_COLS; x++)
	{
		if(!game_board[x])
			return FALSE;
	}
	return TRUE;
}

/*
例えば、
1 2 3      
4 5 6  =>  1 2 3
7 8 9      4 5 6
*/
static void _remap_game_board(const int max_row, char game_board[BOARD_ROWS][BOARD_COLS])
{
	for (int i = max_row; i >= 1; i--)
	{
		for (int j = 0; j < BOARD_COLS; j++)
			game_board[i][j] = game_board[i - 1][j];
	}
	for (int j = 0; j < BOARD_COLS; j++)
		game_board[0][j] = 0;
}

static int _clear_and_count_filled_lines(game_information *info_ptr)
{
    int lines_cleared = 0;
    for (int x = 0; x < BOARD_ROWS; x++)
	{
        if (_is_oneline_filled(info_ptr->game_board[x]))
		{
            _remap_game_board(x, info_ptr->game_board);
            lines_cleared++;
        }
    }
    return lines_cleared;
}

static void _update_game_score(int *score, const int lines_cleared)
{
	*score += SCORE_PER_CELL * BOARD_COLS * lines_cleared;
}

static void _update_interval_time(suseconds_t *interval_time, suseconds_t *drop_speed_up, const int lines_cleared)
{
	*interval_time -= *drop_speed_up * lines_cleared;
}

static void _update_game_information(game_information *info_ptr, const int lines_cleared)
{
	if (lines_cleared > 0)
	{
		_update_game_score(&info_ptr->score, lines_cleared);
		_update_interval_time(&info_ptr->game_time.interval_time, &info_ptr->game_time.drop_speed_up, lines_cleared);
	}
}

void update_game_after_block_fix(game_information *info_ptr)
{
	_fix_block(info_ptr->current_block, info_ptr->game_board);
	int lines_cleared = _clear_and_count_filled_lines(info_ptr);
	_update_game_information(info_ptr, lines_cleared);
	respown_new_block(&info_ptr->current_block);
	if (!is_block_position_valid(info_ptr->current_block, info_ptr->game_board))
		info_ptr->is_game_active = FALSE;
}

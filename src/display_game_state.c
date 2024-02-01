#include "../include/tetris.h"

static void _copy_block_to_buffer(const block_data block, char buffer[BOARD_ROWS][BOARD_COLS])
{
    for (int i = 0; i < block.block_width; i++)
    {
        for (int j = 0; j < block.block_width; j++)
        {
            if (block.block_matrix[i][j])
                buffer[block.position_row + i][block.position_col + j] = block.block_matrix[i][j];
        }
    }
}

void _clear_screen()
{
	clear();
}

static void _print_game_title()
{
	int game_title_length = strlen(GAME_TITLE);
	for(int i = 0; i < BOARD_COLS - game_title_length; i++)
		printw(" ");
	printw("%s\n", GAME_TITLE);
}

static void _print_game_board(const char game_board[BOARD_ROWS][BOARD_COLS], const char buffer[BOARD_ROWS][BOARD_COLS])
{
	for(int x = 0; x < BOARD_ROWS ;x++)
	{
		for(int y = 0; y < BOARD_COLS ; y++)
			printw("%c ", (game_board[x][y] || buffer[x][y]) ? BLOCK_CHAR : BLANK_CHAR);
		printw("\n");
	}
}

static void _print_score(const int score)
{
	printw("\nScore: %d\n", score);
}

void display_game_state(const block_data block, const int score, const char game_board[BOARD_ROWS][BOARD_COLS])
{
	char buffer[BOARD_ROWS][BOARD_COLS] = {{0}};
	_copy_block_to_buffer(block, buffer);
	_clear_screen();
	_print_game_title();
	_print_game_board(game_board, buffer);
	_print_score(score);
}

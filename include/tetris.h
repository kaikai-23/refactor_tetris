#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>


#define TRUE 1
#define FALSE 0
#define BOARD_ROWS 20
#define BOARD_COLS 15
#define LEFT_KEY 'a'
#define RIGHT_KEY 'd'
#define ROTATE_KEY 'w'
#define DOWN_KEY 's'
#define BLOCK_CHAR '#'
#define BLANK_CHAR '.'

#define CURRENT_TIME time(0)
#define NUMBER_OF_BLOCK_SHAPES 7
#define KEYBOARD_INPUT_DELAY_MS 1
#define FIRST_SCORE 0
#define MICROSECONDS_PER_SECOND 1000000
#define INTERVAL_TIME 400000
#define DROP_SPEED_UP 1000
#define SCORE_PER_CELL 100
#define ERROR_MESSAGE "致命的なエラーが発生しました。プログラムを終了します。\n"
#define GAME_TITLE "42 Tetris"
#define GAME_OVER_MESSAGE "Game over!"

typedef struct
{
    char **block_matrix;
    int block_width;
	int position_row;
	int position_col;
} block_data;

typedef struct
{
	suseconds_t interval_time;
	suseconds_t drop_speed_up;
	struct timeval before_now;
	struct timeval now;
} game_time_data;

typedef struct
{
	int score;
	block_data current_block;
	char game_board[BOARD_ROWS][BOARD_COLS];
	bool is_game_active;
	game_time_data game_time;
} game_information;


#include "global_variables.h"
#include "initialization.h"
#include "display_game_state.h"
#include "game_over.h"
#include "game_logic.h"
#include "game_handling.h"
#include "utility.h"
#include "bool_utils.h"
#include "game_state_updates.h"

#endif


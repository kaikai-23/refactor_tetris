#ifndef TEST_H
#define TEST_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

#define BOARD_ROWS 20
#define BOARD_COLS 15
#define BLOCK_CHAR '#'
#define BLANK_CHAR '.'
#define GAME_OVER_MESSAGE "Game over!"
#define TRUE 1
#define FALSE 0

#define FIRST_SCORE 0

#define INTERVAL_TIME 400000
#define DROP_SPEED_UP 1000
#define CURRENT_TIME time(0)

#define NUMBER_OF_BLOCK_SHAPES 7
#define KEYBOARD_INPUT_DELAY_MS 1
#define MICROSECONDS_PER_SECOND 1000000

#define ERROR_MESSAGE "致命的なエラーが発生しました。プログラムを終了します。\n"

#define GAME_TITLE "42 Tetris"

#define LEFT_KEY 'a'
#define RIGHT_KEY 'd'
#define ROTATE_KEY 'w'
#define DOWN_KEY 's'

#define SCORE_PER_CELL 100

typedef struct {
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

// game_over.c(OK)
void display_game_result(int score, char game_board[BOARD_ROWS][BOARD_COLS]);

// initialization.c(OK)
void initialize_game_information(game_information *info_ptr);
void initialize_random_generator();

// display_game_state.c(OK)
void display_game_state(const block_data block, const int score, const char game_board[BOARD_ROWS][BOARD_COLS]);

// utility.c
block_data create_new_block();

// bool_utils.c
bool is_block_position_valid(block_data block, char game_board[BOARD_ROWS][BOARD_COLS]);

#endif

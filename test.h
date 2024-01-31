#ifndef TEST_H
#define TEST_H


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

// grobal_variables(OK)
extern const block_data block_shapes[7];

// initialization.c(OK)
void initialize_game_information(game_information *info_ptr);
void initialize_random_generator();

// display_game_state.c(OK)
void display_game_state(const block_data block, const int score, const char game_board[BOARD_ROWS][BOARD_COLS]);

// game_over.c(OK)
void display_game_result(int score, char game_board[BOARD_ROWS][BOARD_COLS]);

// game_logic.c(OK)
void process_playing_tetris(game_information *info_ptr);

// hundle系(0K)
void handle_key_input(game_information *info_ptr, int pressed_key);
void handle_free_fall(game_information *info_ptr);


// utility.c(OK)
void handle_fatal_error();
void free_block_memory(block_data *block_ptr);
void respown_new_block(block_data *block_ptr);
block_data copy_block(const block_data src);
block_data create_new_block();

// bool_utils.c(OK)
bool is_outside_of_board(const block_data block, const int i, const int j);
bool is_block_position_occupied(const block_data block, const int i, const int j, const char game_board[BOARD_ROWS][BOARD_COLS]);
bool is_block_position_valid(const block_data block, const char game_board[BOARD_ROWS][BOARD_COLS]);
bool should_update_block(const game_time_data time_data);

// game_state_update(OK)
void update_game_after_block_fix(game_information *info_ptr);


#endif

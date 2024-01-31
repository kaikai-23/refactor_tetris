#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#define BOARD_ROWS 20
#define BOARD_COLS 15
#define BLOCK_CHAR '#'
#define BLANK_CHAR '.'
#define GAME_OVER_MESSAGE "Game over!"

void display_game_result(int score, char game_board[BOARD_ROWS][BOARD_COLS]);

#endif

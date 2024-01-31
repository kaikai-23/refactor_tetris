#include "test.h"

static void _print_game_board_state(const char game_board[BOARD_ROWS][BOARD_COLS])
{
    for (int x = 0; x < BOARD_ROWS; x++)
    {
        for (int y = 0; y < BOARD_COLS; y++)
            printf("%c ", game_board[x][y] ? BLOCK_CHAR : BLANK_CHAR);
        printf("\n");
    }
}

static void _print_game_over_message()
{
    printf("\n%s\n", GAME_OVER_MESSAGE);
}

static void _print_final_score(const int score)
{
    printf("\nScore: %d\n", score);
}

void display_game_result(int score, char game_board[BOARD_ROWS][BOARD_COLS])
{
    _print_game_board_state(game_board);
    _print_game_over_message();
    _print_final_score(score);
}

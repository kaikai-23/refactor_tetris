// メモリリークの確認
// #include <libc.h>
// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }
// 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

#define BOARD_ROWS 20
#define BOARD_COLS 15
#define TRUE 1
#define FALSE 0

#define CURRENT_TIME time(0)
#define NUMBER_OF_BLOCK_SHAPES 7
#define KEYBOARD_INPUT_DELAY_MS 1
#define FIRST_SCORE 0

#define MICROSECONDS_PER_SECOND 1000000
#define INTERVAL_TIME 400000
#define DROP_SPEED_UP 1000

#define ERROR_MESSAGE "致命的なエラーが発生しました。プログラムを終了します。\n"

#define GAME_TITLE "42 Tetris"

#define BLOCK_CHAR '#'
#define BLANK_CHAR '.'

#define GAME_OVER_MESSAGE "Game over!"

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

const block_data block_shapes[7]= {
	{(char *[]){(char []){0,1,1},
				(char []){1,1,0},
				(char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1,0},
				(char []){0,1,1}, 
				(char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},
				(char []){1,1,1}, 
				(char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},
				(char []){1,1,1},
				(char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},
				(char []){1,1,1}, 
				(char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},
				(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0}, 
				(char []){1,1,1,1}, 
				(char []){0,0,0,0}, 
				(char []){0,0,0,0}}, 4}
};


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

void handle_fatal_error()
{
	endwin();
	fprintf(stderr, ERROR_MESSAGE);
	exit(EXIT_FAILURE);
}

void free_block_memory(block_data *block_ptr)
{
    for (int i = 0; i < block_ptr->block_width; i++)
		free(block_ptr->block_matrix[i]);
    free(block_ptr->block_matrix);
	block_ptr->block_matrix = NULL;
}

block_data copy_block(block_data src)
{
	// srcのメンバ変数の値をdestへコピー
	block_data dest = {
		.block_width = src.block_width,
		.position_row = src.position_row,
		.position_col = src.position_col
	};

	dest.block_matrix = (char**)malloc(src.block_width * sizeof(char*));
	if (!dest.block_matrix)
		handle_fatal_error();
    for (int i = 0; i < src.block_width; i++)
	{
		dest.block_matrix[i] = (char*)malloc(src.block_width * sizeof(char));
		if (!dest.block_matrix[i])
		{
			free_block_memory(&dest);
			handle_fatal_error();
		}
		for (int j = 0; j < src.block_width; j++)
			dest.block_matrix[i][j] = src.block_matrix[i][j];
    }
    return (dest);
}

void set_keyboard_input_timeout()
{
	timeout(KEYBOARD_INPUT_DELAY_MS);
}

void initialize_random_generator()
{
	srand(CURRENT_TIME);
}

block_data create_new_block()
{
	block_data new_block = copy_block(block_shapes[rand() % NUMBER_OF_BLOCK_SHAPES]);
	new_block.position_col = rand() % (BOARD_COLS - new_block.block_width + 1);
    new_block.position_row = 0;

	return (new_block);
}

bool is_outside_of_board(block_data block, int i, int j)
{
	return (block.position_col + j < 0 || block.position_col + j >= BOARD_COLS || block.position_row + i >= BOARD_ROWS);
}

bool is_block_position_occupied(block_data block, int i, int j, char game_board[BOARD_ROWS][BOARD_COLS])
{
	return (game_board[block.position_row + i][block.position_col + j]);
}

bool is_block_position_valid(block_data block, char game_board[BOARD_ROWS][BOARD_COLS])
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

void copy_block_to_buffer(block_data block, char buffer[BOARD_ROWS][BOARD_COLS])
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

void print_game_title()
{
	int game_title_length = strlen(GAME_TITLE);
	for(int i = 0; i < BOARD_COLS - game_title_length; i++)
		printw(" ");
	printw("%s\n", GAME_TITLE);
}

void print_game_board(char game_board[BOARD_ROWS][BOARD_COLS], char buffer[BOARD_ROWS][BOARD_COLS])
{
	for(int x = 0; x < BOARD_ROWS ;x++)
	{
		for(int y = 0; y < BOARD_COLS ; y++)
			printw("%c ", (game_board[x][y] || buffer[x][y]) ? BLOCK_CHAR : BLANK_CHAR);
		printw("\n");
	}
}

void print_score(int score)
{
	printw("\nScore: %d\n", score);
}

void clear_screen()
{
	clear();
}


void display_game_state(block_data block, int score, char game_board[BOARD_ROWS][BOARD_COLS])
{
	char buffer[BOARD_ROWS][BOARD_COLS] = {0};
	copy_block_to_buffer(block, buffer);
	clear_screen();
	print_game_title();
	print_game_board(game_board, buffer);
	print_score(score);
}

void print_game_board_state(char game_board[BOARD_ROWS][BOARD_COLS])
{
    for (int x = 0; x < BOARD_ROWS; x++)
    {
        for (int y = 0; y < BOARD_COLS; y++)
            printf("%c ", game_board[x][y] ? BLOCK_CHAR : BLANK_CHAR);
        printf("\n");
    }
}

void print_game_over_message()
{
    printf("\n%s\n", GAME_OVER_MESSAGE);
}

void print_final_score(int score)
{
    printf("\nScore: %d\n", score);
}

void display_game_result(int score, char game_board[BOARD_ROWS][BOARD_COLS])
{
    print_game_board_state(game_board);
    print_game_over_message();
    print_final_score(score);
}


/*
90度時計回りに回転
例えば、
1 2 3      7 4 1
4 5 6  =>  8 5 2
7 8 9      9 6 3
*/
void rotate_block(block_data block){
	block_data temp = copy_block(block);
	int width = block.block_width;

	for(int i = 0; i < width ; i++)
	{
		for(int j = 0, k = width - 1; j < width ; j++, k--)
			block.block_matrix[i][j] = temp.block_matrix[k][i];
	}
	free_block_memory(&temp);
}

bool should_update_block(game_time_data time_data){
	suseconds_t current_time, previous_time;

	current_time = time_data.now.tv_sec * MICROSECONDS_PER_SECOND + time_data.now.tv_usec;
	previous_time = time_data.before_now.tv_sec * MICROSECONDS_PER_SECOND + time_data.before_now.tv_usec;

	return (current_time - previous_time > time_data.interval_time);
}

void fix_block(block_data block, char game_board[BOARD_ROWS][BOARD_COLS])
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

bool is_oneline_filled(char game_board[BOARD_COLS])
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
void remap_game_board(int max_row, char game_board[BOARD_ROWS][BOARD_COLS])
{
	for (int i = max_row; i >= 1; i--)
	{
		for (int j = 0; j < BOARD_COLS; j++)
			game_board[i][j] = game_board[i - 1][j];
	}
	for (int j = 0; j < BOARD_COLS; j++)
		game_board[0][j] = 0;
}

void update_game_score(int *score, int lines_cleared)
{
	*score += SCORE_PER_CELL * BOARD_COLS * lines_cleared;
}

void update_interval_time(suseconds_t *interval_time, suseconds_t *drop_speed_up, int lines_cleared)
{
	*interval_time -= *drop_speed_up * lines_cleared;
}

void respown_new_block(block_data *block_ptr)
{
	block_data new_block = create_new_block();

	free_block_memory(block_ptr);
	*block_ptr = new_block;
}

void update_game_information(game_information *info_ptr, int lines_cleared)
{
	if (lines_cleared > 0)
	{
		update_game_score(&info_ptr->score, lines_cleared);
		update_interval_time(&info_ptr->game_time.interval_time, &info_ptr->game_time.drop_speed_up, lines_cleared);
	}
}

int clear_and_count_filled_lines(game_information *info_ptr)
{
    int lines_cleared = 0;
    for (int x = 0; x < BOARD_ROWS; x++)
	{
        if (is_oneline_filled(info_ptr->game_board[x]))
		{
            remap_game_board(x, info_ptr->game_board);
            lines_cleared++;
        }
    }
    return lines_cleared;
}

void update_game_after_block_fix(game_information *info_ptr)
{
	fix_block(info_ptr->current_block, info_ptr->game_board);
	int lines_cleared = clear_and_count_filled_lines(info_ptr);
	update_game_information(info_ptr, lines_cleared);
	respown_new_block(&info_ptr->current_block);
	if (!is_block_position_valid(info_ptr->current_block, info_ptr->game_board))
		info_ptr->is_game_active = FALSE;
}


void move_block_down(game_information *info_ptr)
{
	block_data temp = copy_block(info_ptr->current_block);
	temp.position_row++;
    if (is_block_position_valid(temp, info_ptr->game_board))
        info_ptr->current_block.position_row++;
    else
        update_game_after_block_fix(info_ptr);
    free_block_memory(&temp);
}

void move_block_right(game_information *info_ptr)
{
    block_data temp = copy_block(info_ptr->current_block);
    temp.position_col++;
    if (is_block_position_valid(temp, info_ptr->game_board))
        info_ptr->current_block.position_col++;
    free_block_memory(&temp);
}

void move_block_left(game_information *info_ptr)
{
    block_data temp = copy_block(info_ptr->current_block);
    temp.position_col--;
    if (is_block_position_valid(temp, info_ptr->game_board))
        info_ptr->current_block.position_col--;
    free_block_memory(&temp);
}

void move_block_rotate(game_information *info_ptr)
{
    block_data temp = copy_block(info_ptr->current_block);
	rotate_block(temp);
	if (is_block_position_valid(temp, info_ptr->game_board))
		rotate_block(info_ptr->current_block);
	free_block_memory(&temp);
}

void handle_key_input(game_information *info_ptr, int pressed_key)
{
	switch (pressed_key)
	{
	case DOWN_KEY:
		move_block_down(info_ptr);
		break;
	case RIGHT_KEY:
		move_block_right(info_ptr);
		break;
	case LEFT_KEY:
		move_block_left(info_ptr);
		break;
	case ROTATE_KEY:
		move_block_rotate(info_ptr);
		break;
	}
}

void handle_free_fall(game_information *info_ptr)
{
	gettimeofday(&info_ptr->game_time.now, NULL);
	if (should_update_block(info_ptr->game_time))
	{
		move_block_down(info_ptr);
		gettimeofday(&info_ptr->game_time.before_now, NULL);
	}
}

void process_playing_tetris(game_information *info_ptr)
{
	set_keyboard_input_timeout();
	while(info_ptr->is_game_active)
	{
		int pressed_key = getch();
		if(pressed_key != ERR)
			handle_key_input(info_ptr, pressed_key);
		handle_free_fall(info_ptr);
		display_game_state(info_ptr->current_block, info_ptr->score, info_ptr->game_board);
	}
}

int main()
{
	game_information game_info;

	initialize_random_generator();
	initscr();
	initialize_game_information(&game_info);

	display_game_state(game_info.current_block, game_info.score, game_info.game_board);

	process_playing_tetris(&game_info);

	free_block_memory(&game_info.current_block);
	endwin();
	display_game_result(game_info.score, game_info.game_board);
}

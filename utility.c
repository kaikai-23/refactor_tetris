#include "test.h"

// const block_data block_shapes[7]= {
// 	{(char *[]){(char []){0,1,1},
// 				(char []){1,1,0},
// 				(char []){0,0,0}}, 3},
// 	{(char *[]){(char []){1,1,0},
// 				(char []){0,1,1}, 
// 				(char []){0,0,0}}, 3},
// 	{(char *[]){(char []){0,1,0},
// 				(char []){1,1,1}, 
// 				(char []){0,0,0}}, 3},
// 	{(char *[]){(char []){0,0,1},
// 				(char []){1,1,1},
// 				(char []){0,0,0}}, 3},
// 	{(char *[]){(char []){1,0,0},
// 				(char []){1,1,1}, 
// 				(char []){0,0,0}}, 3},
// 	{(char *[]){(char []){1,1},
// 				(char []){1,1}}, 2},
// 	{(char *[]){(char []){0,0,0,0}, 
// 				(char []){1,1,1,1}, 
// 				(char []){0,0,0,0}, 
// 				(char []){0,0,0,0}}, 4}
// };

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

void respown_new_block(block_data *block_ptr)
{
	block_data new_block = create_new_block();

	free_block_memory(block_ptr);
	*block_ptr = new_block;
}

block_data copy_block(const block_data src)
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

block_data create_new_block()
{
	block_data new_block = copy_block(block_shapes[rand() % NUMBER_OF_BLOCK_SHAPES]);
	new_block.position_col = rand() % (BOARD_COLS - new_block.block_width + 1);
    new_block.position_row = 0;

	return (new_block);
}

// メモリリークの確認
// #include <libc.h>
// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }
// 

#include "../include/tetris.h"

int main()
{
	game_information game_info;

	initscr();
	initialize_random_generator();
	initialize_game_information(&game_info);

	display_game_state(game_info.current_block, game_info.score, game_info.game_board);

	process_playing_tetris(&game_info);

	free_block_memory(&game_info.current_block);
	endwin();
	display_game_result(game_info.score, game_info.game_board);
}

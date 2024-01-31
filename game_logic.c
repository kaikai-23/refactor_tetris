#include "test.h"

static void _set_keyboard_input_timeout()
{
	timeout(KEYBOARD_INPUT_DELAY_MS);
}

void process_playing_tetris(game_information *info_ptr)
{
	_set_keyboard_input_timeout();
	while(info_ptr->is_game_active)
	{
		int pressed_key = getch();
		if(pressed_key != ERR)
			handle_key_input(info_ptr, pressed_key);
		handle_free_fall(info_ptr);
		display_game_state(info_ptr->current_block, info_ptr->score, info_ptr->game_board);
	}
}

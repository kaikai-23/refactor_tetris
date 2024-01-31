#ifndef UTILITY_H
#define UTILITY_H

#include "tetris.h"

void handle_fatal_error();
void free_block_memory(block_data *block_ptr);
void respown_new_block(block_data *block_ptr);
block_data copy_block(const block_data src);
block_data create_new_block();

#endif

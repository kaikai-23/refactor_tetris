NAME = tetris
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = include/
SRCS = 	main.c \
		game_over.c \
		initialization.c \
		display_game_state.c \
		game_logic.c \
		game_handling.c \
		utility.c \
		bool_utils.c \
		game_state_updates.c \
		global_variables.c
SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lncurses

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

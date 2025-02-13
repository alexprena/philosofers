

NAME = philo
NAME_DEBUG = 
FLAGS = -Wall -Werror -Wextra -g  -pthread
INCLUDES = -I ./inc/
SRC = main.c parsing.c utils.c simulation_utils.c actions.c

DIR_SRC = ./src
DIR_OBJ = $(DIR_SRC)/obj
OBJ = $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
DEP = $(addprefix $(DIR_OBJ)/, $(SRC:.c=.d))


all: dir $(NAME)

debug: dir compile_debug

val: ./$(NAME) 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME) 124 500 230 200
	
-include $(DEP)

dir:
	mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c Makefile
	$(CC) -MMD $(FLAGS)  -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ $(INCLUDES)
	echo "$(NAME) compilao!"

compile_debug: $(OBJ)
	$(CC) $(FLAGS) -fsanitize=thread $(OBJ) -o $(NAME) $(INCLUDES)

clean:
	rm -rf $(DIR_OBJ)
	echo "borrao"

fclean: clean
	rm -rf $(NAME)
	echo "to borrao"

re: fclean all

.PHONY: fclean all clean re dir debug val
.SILENT:

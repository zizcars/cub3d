
# ANSI color codes
RESET = \033[0m
BOLD = \033[1m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
CC = cc
NAME = cub3D

CFLAGS =  -g -fsanitize=address

# -Wall -Wextra -Werror
# SRC =	src/main.c src/display.c src/raycasting.c src/parsing.c src/array.c src/check.c \
# 		libs/getnextline/get_next_line.c libs/getnextline/get_next_line_utils.c \
# 		src/texture.c src/check_map.c src/

SRC = $(wildcard src/*.c) 

OBJ = $(SRC:.c=.o)

LIB = libs/libft/libft.a libs/MLX42/build/libmlx42.a

MLXFLAGS = -Iinclude -lglfw -L"/Users/$(USER)/goinfre/homebrew/Cellar/glfw/3.4/lib/" #in school mac
# MLXFLAGS = -Iinclude -lglfw # in my mac

INCLUDES = includes/parsing.h includes/types.h 

all: $(NAME) 

$(NAME): $(OBJ) #mlxlib 
	@echo "$(BOLD)$(BLUE)┌──── Building $(NAME) ────┐$(RESET)"
	@echo " $(YELLOW)Compiling libft...$(RESET)"
	@make -C libs/libft
	@echo " $(YELLOW)Linking object files...$(RESET)"
	@cc $(CFLAGS) $(OBJ) $(LIB) $(MLXFLAGS) -o $(NAME) 
	@echo "$(BLUE)└──── Build complete ────┘$(RESET)"
	@echo "$(GREEN)$(BOLD)🎮 $(NAME) is ready to play! 🎮$(RESET)"

%.o: %.c $(INCLUDES) # YOU HAVE TO FIX THAT IT NOT WORKING
	echo "$(CYAN)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

mlxlib:
	@echo "$(MAGENTA)Building MLX library...$(RESET)"
	@cd libs/MLX42/ && cmake -B build && cmake --build build -j4 && cd ..

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@make clean -C libs/libft
	@rm -f $(OBJ)
	@rm -f libs/getnextline/get_next_line_utils.o libs/getnextline/get_next_line.o

fclean: clean
	@echo "$(RED)Removing executable and libraries...$(RESET)"
	@make fclean -C libs/libft
	@rm -f $(NAME)
	@echo "$(GREEN)Cleanup complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re mlxlib

# build:
# 	brew install glfw
# 	brew install cmake
# 	git clone https://github.com/codam-coding-college/MLX42.git

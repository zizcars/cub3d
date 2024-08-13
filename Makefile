# NAME = cub3d
# CFLAGES = -Wall -Wextra -Werror
# SRC = main.c parsing.c getnextline/get_next_line.c getnextline/get_next_line_utils.c
# OBJ = $(SRC:.c=.o)
# LIB = libft/libft.a libmlx.dylib
# MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

# all : $(NAME)

# $(NAME) : $(OBJ) mlxlib
# 	make -C libft
# 	cc $(CFLAGES) $(OBJ) $(LIB) -o $(NAME)

# mlxlib: 
# 	Make -C mlx
# 	mv mlx/libmlx.dylib .

# clean : 
# 	make clean -C libft
# 	make clean -C mlx
# 	rm -f $(OBJ) libmlx.dylib
# 	rm -f getnextline/get_next_line_utils.o getnextline/get_next_line.o

# fclean : clean
# 	make fclean -C libft
# 	rm -f $(NAME)

# re : fclean all

NAME = cub3d
CFLAGS = -Wall -Wextra -Werror
SRC = main.c parsing.c getnextline/get_next_line.c getnextline/get_next_line_utils.c
OBJ = $(SRC:.c=.o)
LIB = libft/libft.a libmlx.dylib
MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

# ANSI color codes
RESET = \033[0m
BOLD = \033[1m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m

# Unicode characters for box drawing
BOX_TL = ┌
BOX_TR = ┐
BOX_BL = └
BOX_BR = ┘
BOX_H = ─
BOX_V = │

all: $(NAME)

$(NAME): $(OBJ) mlxlib
	@echo "$(BOLD)$(BLUE)┌──── Building $(NAME) ────┐$(RESET)"
	@echo " $(YELLOW)Compiling libft...$(RESET)"
	@make -C libft
	@echo " $(YELLOW)Linking object files...$(RESET)"
	@cc $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)
	@echo "$(BLUE)└──── Build complete ────┘$(RESET)"
	@echo "$(GREEN)$(BOLD)🎮 $(NAME) is ready to play! 🎮$(RESET)"

%.o: %.c
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@cc $(CFLAGS) -c $< -o $@

mlxlib:
	@echo "$(MAGENTA)Building MLX library...$(RESET)"
	@make -C mlx
	@mv mlx/libmlx.dylib .

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@make clean -C libft
	@make clean -C mlx
	@rm -f $(OBJ) libmlx.dylib
	@rm -f getnextline/get_next_line_utils.o getnextline/get_next_line.o

fclean: clean
	@echo "$(RED)Removing executable and libraries...$(RESET)"
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "$(GREEN)Cleanup complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re mlxlib

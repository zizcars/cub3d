
NAME = cub3D
# -Wall -Wextra -Werror 
CFLAGS = -g -fsanitize=address

SRC =	src/main.c src/display.c src/raycasting.c src/parsing.c src/array.c src/check.c \
		libs/getnextline/get_next_line.c libs/getnextline/get_next_line_utils.c \
		src/texture.c

# SRC = test.c

OBJ = $(SRC:.c=.o)

LIB = libs/libft/libft.a libs/MLX42/build/libmlx42.a

MLXFLAGS = -Iinclude -lglfw -L"/Users/$(USER)/goinfre/homebrew/Cellar/glfw/3.4/lib/" #in school mac
# MLXFLAGS = -Iinclude -lglfw # in my mac

INCLUDES = includes/parsing.h includes/types.h 

all: $(NAME)

$(NAME): $(OBJ) #mlxlib
	make -C libs/libft
	cc $(CFLAGS) $(OBJ) $(LIB) $(MLXFLAGS) -o $(NAME) 
	


# we need flags CFLAGS
%.o: %.c $(INCLUDES)
	cc $(CFLAGS) -c  $< -o $@

mlxlib:
	cd libs/MLX42/ && cmake -B build && cmake --build build -j4 && cd ..

clean:
	make clean -C libs/libft
	rm -f $(OBJ)
	rm -f libs/getnextline/get_next_line_utils.o libs/getnextline/get_next_line.o

fclean: clean
	make fclean -C libs/libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mlxlib


# build:
# 	brew install glfw
# 	brew install cmake
# 	git clone https://github.com/codam-coding-college/MLX42.git


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

# NAME = cub3d
# CFLAGS = -Wall -Wextra -Werror
# # SRC = main.c parsing.c getnextline/get_next_line.c getnextline/get_next_line_utils.c
# SRC = test.c
# OBJ = $(SRC:.c=.o)
# LIB = libft/libft.a libmlx42.a
# # MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
# MLXFLAGS = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

# # ANSI color codes
# RESET = \033[0m
# BOLD = \033[1m
# RED = \033[31m
# GREEN = \033[32m
# YELLOW = \033[33m
# BLUE = \033[34m
# MAGENTA = \033[35m
# CYAN = \033[36m

# # Unicode characters for box drawing
# BOX_TL = ┌
# BOX_TR = ┐
# BOX_BL = └
# BOX_BR = ┘
# BOX_H = ─
# BOX_V = │

# all: $(NAME)

# $(NAME): $(OBJ) mlxlib
# 	@echo "$(BOLD)$(BLUE)┌──── Building $(NAME) ────┐$(RESET)"
# 	@echo " $(YELLOW)Compiling libft...$(RESET)"
# 	@make -C libft
# 	@echo " $(YELLOW)Linking object files...$(RESET)"
# 	@cc $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)
# 	@echo "$(BLUE)└──── Build complete ────┘$(RESET)"
# 	@echo "$(GREEN)$(BOLD)🎮 $(NAME) is ready to play! 🎮$(RESET)"

# %.o: %.c
# 	@echo "$(CYAN)Compiling $<...$(RESET)"
# 	@cc $(CFLAGS) $(MLXFLAGS) -c $< -o $@

# mlxlib:
# 	@echo "$(MAGENTA)Building MLX library...$(RESET)"
# 	@bash -c "cd MLX42" && "cmake -B build" && "cmake --build build -j4" && "cd -"
# 	@mv MLX42/build/libmlx42.a .

# clean:
# 	@echo "$(RED)Cleaning object files...$(RESET)"
# 	@make clean -C libft
# # @make clean -C mlx
# 	@rm -f $(OBJ) libmlx42.a
# 	@rm -f getnextline/get_next_line_utils.o getnextline/get_next_line.o

# fclean: clean
# 	@echo "$(RED)Removing executable and libraries...$(RESET)"
# 	@make fclean -C libft
# 	@rm -f $(NAME)
# 	@echo "$(GREEN)Cleanup complete!$(RESET)"

# re: fclean all

# .PHONY: all clean fclean re mlxlib



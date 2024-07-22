CFLAGES = -Wall -Wextra -Werror
SRC = main.c parsing.c getnextline/get_next_line.c getnextline/get_next_line_utils.c
NAME = cub3d
OBJ = $(SRC:.c=.o)
LIB = libft/libft.a 

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft
	cc $(CFLAGES) $(OBJ) $(LIB) -o $(NAME)

clean : 
	make clean -C libft
	rm -f $(OBJ)
	rm -f getnextline/get_next_line_utils.o getnextline/get_next_line.o

fclean : clean
	make fclean -C libft
	rm -f $(NAME)

re : fclean all

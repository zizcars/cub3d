
#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include "../libs/libft/libft.h"
#include "../libs/getnextline/get_next_line.h"
#include "../libs/MLX42/include/MLX42/MLX42.h"

#define SPACE 32

// typedef struct s_row
// {
// 	char *row;
// 	struct s_row *next;
// } t_row;

typedef struct s_map_info
{
	char *north_path;
	char *south_path;
	char *west_path;
	char *east_path;
	char *floor_color;
	char *ceiling_color;
	char **arr_map;
	// char *map;
} t_map_info;

#endif

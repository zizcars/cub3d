
#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "getnextline/get_next_line.h"
#include "mlx/mlx.h"

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
	// char **map;
	char *map;
} t_map_info;

#endif

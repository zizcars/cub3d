
#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include "../libs/libft/libft.h"
#include "../libs/getnextline/get_next_line.h"
#include "../libs/MLX42/include/MLX42/MLX42.h"

#define SPACE 32
#define W 400
#define H 400
#define SIZE 20

typedef struct s_info
{
	char *north_path;
	char *south_path;
	char *west_path;
	char *east_path;
	char *floor_color;
	int *f_color;
	char *ceiling_color;
	int *c_color;
	char **arr_map;
	int width;
	int height;
	int x_player;
	int y_player;
	// char *map;
} t_info;

typedef struct s_mlx
{
	mlx_t *mlx;
	mlx_image_t *image;
	mlx_image_t *p_image;
	int width;
	int height;
	t_info *info;
} t_mlx;

#endif

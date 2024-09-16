
#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include "math.h"
#include "../libs/libft/libft.h"
#include "../libs/getnextline/get_next_line.h"
#include "../libs/MLX42/include/MLX42/MLX42.h"

#define SPACE 32
// #define W 400
// #define H 400
#define SIZE 20
#define STEP_SIZE 5
#define PI 3.14159265

typedef struct s_info
{
	char *north_path;
	char *south_path;
	char *west_path;
	char *east_path;
	int *f_color;
	int *c_color;
	char **arr_map;
	int width;
	int height;
	int player_x;
	int player_y;
	float player_angle; // player angle N, W , S, E 
	float player_fov; // player Field of View
} t_info;

typedef struct s_mlx
{
	mlx_t *mlx;
	mlx_image_t *image;
	t_info *info;
} t_mlx;

#endif


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
#define TAB 9
// #define WIDTH 400
// #define HEIGHT 400
#define SIZE 20
#define STEP_SIZE 5
// #define PI 180

#define WALL_COLOR 18, 25, 41
#define FLOOR_COLOR  79, 86, 89
#define PERSON_COLOR 109, 184, 194
#define RAYS_COLOR 211, 215, 237

typedef struct s_info
{
	char *north_path;
	char *south_path;  // they store the path to n, s, w, e textures
	char *west_path;
	char *east_path; 
	int *f_color; // floor color as [r, g, b]
	int *c_color; // celling color as [r, g, b]
	char **arr_map; // the map as an array of lines
	int width; // the width of the map, the width of the window is width * SIZE
	int height; // the height of the map, the height of the window is height * SIZE
	int player_x; // position of the player x
	int player_y; // position of the player y
	float player_angle; // player angle N, W , S, E 
	float player_fov; // player Field of View
} t_info;

typedef struct s_mlx
{
	mlx_t *mlx;
	mlx_image_t *map_image;
	mlx_image_t *r_image;
	t_info *info;
} t_mlx;

#endif

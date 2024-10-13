
#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include "math.h"
#include "../libs/libft/libft.h"
#include "../libs/getnextline/get_next_line.h"
#include "../libs/MLX42/include/MLX42/MLX42.h"

#define WIDTH 1280
#define HEIGHT 720
#define BOX 20

#define FACTOR 0.4
#define ROTATION_ANGLE 5
#define SPACE 32
#define TAB 9
#define SIZE 20
#define STEP_SIZE 6
// #define PI 180
#define PLAYER_FOV (60 * M_PI) / 180.0f

#define WALL_COLOR 1, 22, 30
#define FLOOR_COLOR  239, 246, 224
#define PERSON_COLOR 174, 195, 176
#define SPACE_COLOR 18, 69, 89
#define RAYS_COLOR 211, 215, 237
#define FRAME_COLOR 255, 183, 3

typedef enum{
	UP = 1,
	DOWN = 2,
	RIGHT = 3,
	LEFT = 4,
} E_DIRECTION;

typedef struct s_texture
{
	uint32_t *pixels;
	uint32_t height;
	uint32_t width;
} t_texture;

typedef struct s_info
{
	char *north_path;
	char *south_path;  // they store the path to n, s, w, e textures
	char *west_path;
	char *east_path; 
	mlx_texture_t *texture[4];
	int *f_color; // floor color as [r, g, b]
	int *c_color; // celling color as [r, g, b]
	char **arr_map; // the map as an array of lines
	int width; // the width of the map, the width of the window is width * SIZE
	int height; // the height of the map, the height of the window is height * SIZE
	int player_x; // position of the player x
	int player_y; // position of the player y
	double player_angle; // player angle N, W , S, E 
	int check_x;
	int check_y;
	// double correct_angle;
} t_info;


typedef struct s_point
{
	double x;
	double y;
	double distance;
	bool vertical;
	double angle;
	int ray;
} t_point;

typedef struct s_mlx
{
	mlx_t *mlx;
	mlx_image_t *map_image;
	mlx_image_t *floor_image;
	mlx_image_t *minimapfloor_image;
	mlx_image_t *r_image;
	t_info *info;
} t_mlx;


#endif

#include "../includes/utiles.h"

void display_mini_map_ground(mlx_image_t *img)
{
	int y;
	int x;

	y = 0;
	while (y < FRAME_Y)
	{
		x = 0;
		while (x < FRAME_X)
		{
			mlx_put_pixel(img, x, y, get_rgba(SPACE_COLOR));
			x++;
		}
		y++;
	}
}

void draw_map(t_mlx mlx, int y, int i)
{
	int j;
	int x;

	j = mlx.info->player_x - FRAME_X / 2;
	x = 0;
	while (x < FRAME_X)
	{
		if (j < 0)
		{
			x++;
			j++;
			continue;
		}
		if (mlx.info->arr_map[(int)(i / (SIZE))] && (int)ft_strlen(mlx.info->arr_map[(int)(i / SIZE)]) > j / SIZE)
		{
			if (!mlx.info->arr_map[(int)(i / SIZE)][(int)(j / SIZE)])
				break;
			if (mlx.info->arr_map[(int)(i / SIZE)][(int)(j / SIZE)] == '1')
				mlx_put_pixel(mlx.map_image, x, y, get_rgba(WALL_COLOR));
			else if (mlx.info->arr_map[(int)(i / SIZE)][(int)(j / SIZE)] != SPACE)
				mlx_put_pixel(mlx.map_image, x, y, get_rgba(FLOOR_COLOR));
		}
		x++;
		j++;
	}
}

void draw_point(mlx_image_t *img, int x, int y)
{
	mlx_put_pixel(img, x, y, get_rgba(FOCUS_COLOR));
	mlx_put_pixel(img, x, y + 1, get_rgba(FOCUS_COLOR));
	mlx_put_pixel(img, x + 1, y, get_rgba(FOCUS_COLOR));
	mlx_put_pixel(img, x + 1, y + 1, get_rgba(FOCUS_COLOR));
}

void draw_focus_point(mlx_image_t *img)
{
	int i;

	draw_point(img, WIDTH / 2, HEIGHT / 2);
	i = 6;
	while (i < 10)
		draw_point(img, WIDTH / 2 + i++, HEIGHT / 2);
	i = 6;
	while (i < 10)
		draw_point(img, WIDTH / 2 - i++, HEIGHT / 2);
	i = 6;
	while (i < 10)
		draw_point(img, WIDTH / 2, HEIGHT / 2 + i++);
	i = 6;
	while (i < 10)
		draw_point(img, WIDTH / 2, HEIGHT / 2 - i++);
}

void display_map(t_mlx *mlx)
{
	int y;
	int i;

	mlx_delete_image(mlx->mlx, mlx->map_image);
	mlx->map_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx->mlx, mlx->minimapfloor_image, 0, 0);
	i = mlx->info->player_y - FRAME_Y / 2;
	y = 0;
	while (y < FRAME_Y)
	{
		if (i < 0)
		{
			i++;
			y++;
			continue;
		}
		if (!mlx->info->arr_map[(int)(i / (SIZE))])
			break;
		draw_map(*mlx, y, i);
		i++;
		y++;
	}
	draw_focus_point(mlx->map_image);
	display_person(mlx->map_image, FRAME_X / 2, FRAME_Y / 2);
	mlx_image_to_window(mlx->mlx, mlx->map_image, 0, 0);
}


#include "../includes/types.h"
#include "../includes/parsing.h"

void put_pixel(t_mlx *mlx, int x, int y, int color)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			mlx_put_pixel(mlx->image, x + i, y + j, color);
	}
	// mlx_image_to_window(mlx->mlx, mlx->image, 0, 0);
}

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void display_square(t_mlx mlx, int color, const int x, const int y)
{
	int i;
	int j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			mlx_put_pixel(mlx.image, i + x, j + y, color);
			j++;
		}
		i++;
	}
}

void display_person(t_mlx mlx, const int x, const int y)
{
	float i, j, a;
	i = j = a = 0;
	while (a < 2 * M_PI)
	{
		i = x + 2.0f * cos(a);
		j = y + 2.0f * sin(a);
		mlx_put_pixel(mlx.image, i, j, get_rgba(PERSON_COLOR, 255));
		a += 0.1f;
	}
}

void display_map(t_mlx mlx)
{
	int i;
	int j;
	int x;
	int y;

	y = 0;
	i = 0;
	while (mlx.info->arr_map[i])
	{
		j = 0;
		x = 0;
		while (mlx.info->arr_map[i][j])
		{
			if (mlx.info->arr_map[i][j] == '1')
				display_square(mlx, get_rgba(WALL_COLOR , 255), x, y);
			else
				display_square(mlx, get_rgba(FLOOR_COLOR, 255), x, y);
			j++;
			x += SIZE;
		}
		y += SIZE;
		i++;
	}
}

void keyhook(mlx_key_data_t keydata, void *param)
{
	t_mlx *mlx = (t_mlx *)param;

	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (mlx->info->arr_map[(mlx->info->player_y - STEP_SIZE) / SIZE][mlx->info->player_x / SIZE] != '1')
			mlx->info->player_y -= STEP_SIZE;
	}
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (mlx->info->arr_map[(mlx->info->player_y + STEP_SIZE) / SIZE][mlx->info->player_x / SIZE] != '1')
			mlx->info->player_y += STEP_SIZE;
	}
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (mlx->info->arr_map[mlx->info->player_y / SIZE][(mlx->info->player_x + STEP_SIZE) / SIZE] != '1')
			mlx->info->player_x += STEP_SIZE;
	}
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (mlx->info->arr_map[mlx->info->player_y / SIZE][(mlx->info->player_x - STEP_SIZE) / SIZE] != '1')
			mlx->info->player_x -= STEP_SIZE; //change this to something depand on the angle
	}
	else if (keydata.key == MLX_KEY_ESCAPE)
		exit(0); // i think here some leaks
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		mlx->info->player_angle += 10;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		mlx->info->player_angle -= 10;
	else
		return;
	mlx_delete_image(mlx->mlx, mlx->image);
	mlx->image = mlx_new_image(mlx->mlx, mlx->info->width * SIZE, mlx->info->height * SIZE);
	display_map(*mlx);
	display_rays(*mlx);
	display_person(*mlx, mlx->info->player_x, mlx->info->player_y);
	mlx_image_to_window(mlx->mlx, mlx->image, 0, 0);
}

void display_window(t_mlx *mlx)
{
	mlx->mlx = mlx_init(mlx->info->width * SIZE, mlx->info->height * SIZE, "CUB3D", true);
	mlx->image = mlx_new_image(mlx->mlx, mlx->info->width * SIZE, mlx->info->height * SIZE);
	display_map(*mlx);
	display_rays(*mlx);
	// put_pixel(mlx, mlx->info->player_x, mlx->info->player_y, get_rgba(0, 255, 0, 255));
	display_person(*mlx, mlx->info->player_x, mlx->info->player_y);
	mlx_image_to_window(mlx->mlx, mlx->image, 0, 0);
	mlx_key_hook(mlx->mlx, keyhook, mlx);
	mlx_loop(mlx->mlx);
}

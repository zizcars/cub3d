
#include "../includes/types.h"
#include "../includes/parsing.h"

void put_pixel(mlx_image_t *image, int x, int y, int color)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			mlx_put_pixel(image, x + i, y + j, color);
	}
	// mlx_image_to_window(mlx->mlx, mlx->image, 0, 0);
}

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void display_square(mlx_image_t *image, int color, const int x, const int y)
{
	int i;
	int j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			mlx_put_pixel(image, i + x, j + y, color);
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
		mlx_put_pixel(mlx.r_image, i, j, get_rgba(PERSON_COLOR, 255));
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
				display_square(mlx.map_image, get_rgba(WALL_COLOR, 255), x, y);
			else
				display_square(mlx.map_image, get_rgba(FLOOR_COLOR, 255), x, y);
			j++;
			x += SIZE;
		}
		y += SIZE;
		i++;
	}
	mlx_image_to_window(mlx.mlx, mlx.map_image, 0, 0);
}

void keyhook(mlx_key_data_t keydata, void *param)
{
	t_mlx *mlx = (t_mlx *)param;
	int tmp_y;
	int tmp_x;

	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		tmp_y = mlx->info->player_y + sin(mlx->info->player_angle) * STEP_SIZE;
		tmp_x = mlx->info->player_x + cos(mlx->info->player_angle) * STEP_SIZE;
		// printf("tmp_y:%d sin(a) = %lf y: %d\n", tmp_y, mlx->info->player_x);
		if (mlx->info->arr_map[tmp_y / SIZE][tmp_x / SIZE] != '1')
		{
			mlx->info->player_y = tmp_y;
			mlx->info->player_x = tmp_x;
		}
	}
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		tmp_y = mlx->info->player_y - sin(mlx->info->player_angle) * STEP_SIZE;
		tmp_x = mlx->info->player_x - cos(mlx->info->player_angle) * STEP_SIZE;
		if (mlx->info->arr_map[tmp_y / SIZE][tmp_x / SIZE] != '1')
		{
			mlx->info->player_y = tmp_y;
			mlx->info->player_x = tmp_x;
		}
	}
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		tmp_y = mlx->info->player_y + sin(mlx->info->player_angle + (90 * M_PI) / 180) * STEP_SIZE;
		tmp_x = mlx->info->player_x + cos(mlx->info->player_angle + (90 * M_PI) / 180) * STEP_SIZE;
		if (mlx->info->arr_map[tmp_y / SIZE][tmp_x / SIZE] != '1')
		{
			mlx->info->player_y = tmp_y;
			mlx->info->player_x = tmp_x;
		}
	}
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		tmp_x = mlx->info->player_x + cos(mlx->info->player_angle - (90 * M_PI) / 180) * STEP_SIZE;
		tmp_y = mlx->info->player_y + sin(mlx->info->player_angle - (90 * M_PI) / 180) * STEP_SIZE;
		if (mlx->info->arr_map[tmp_y / SIZE][tmp_x / SIZE] != '1')
		{
			mlx->info->player_y = tmp_y;
			mlx->info->player_x = tmp_x;
		}
	}
	else if (keydata.key == MLX_KEY_ESCAPE)
		exit(0); // i think here some leaks
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		mlx->info->player_angle += (10 * M_PI) / 180.0f;
		if (mlx->info->player_angle > (360 * M_PI) / 180.0f)
			mlx->info->player_angle -= ((360 * M_PI) / 180.0f);
		// else if (mlx->info->player_angle < 0)
		// 	mlx->info->player_angle += ((360 * M_PI) / 180.0f);
	}
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		mlx->info->player_angle -= (10 * M_PI) / 180.0f;
		// if (mlx->info->player_angle > (360 * M_PI) / 180.0f)
		// 	mlx->info->player_angle -= ((360 * M_PI) / 180.0f);
		if (mlx->info->player_angle < 0)
			mlx->info->player_angle += ((360 * M_PI) / 180.0f);
	}
	else
		return;
	mlx_delete_image(mlx->mlx, mlx->r_image);
	mlx->r_image = mlx_new_image(mlx->mlx, mlx->info->width * SIZE, mlx->info->height * SIZE);
	display_rays(mlx);
	display_person(*mlx, mlx->info->player_x, mlx->info->player_y);
	mlx_image_to_window(mlx->mlx, mlx->r_image, 0, 0);
}

void display_window(t_mlx *mlx)
{
	mlx->mlx = mlx_init(mlx->info->width * SIZE, mlx->info->height * SIZE, "CUB3D", true);
	mlx->map_image = mlx_new_image(mlx->mlx, mlx->info->width * SIZE, mlx->info->height * SIZE);
	mlx->r_image = mlx_new_image(mlx->mlx, mlx->info->width * SIZE, mlx->info->height * SIZE);
	display_map(*mlx);
	display_rays(mlx);
	// put_pixel(mlx, mlx->info->player_x, mlx->info->player_y, get_rgba(0, 255, 0, 255));
	display_person(*mlx, mlx->info->player_x, mlx->info->player_y);
	mlx_image_to_window(mlx->mlx, mlx->r_image, 0, 0);
	mlx_key_hook(mlx->mlx, keyhook, mlx);
	mlx_loop(mlx->mlx);
}


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
			else if (mlx.info->arr_map[i][j] != SPACE)
				display_square(mlx.map_image, get_rgba(FLOOR_COLOR, 255), x, y);
			j++;
			x += SIZE;
		}
		y += SIZE;
		i++;
	}
	mlx_image_to_window(mlx.mlx, mlx.map_image, 0, 0);
}

double angle_corrector(double angle)
{
	if (angle > (360 * M_PI) / 180.0f)
		angle -= ((360 * M_PI) / 180.0f);
	else if (angle < 0)
		angle += ((360 * M_PI) / 180.0f);
	return (angle);
}

static bool is_gape(char **map, int x, int y, int nx, int ny)
{
	if (map[ny][nx] != '1' && map[ny][nx] != '\0' && map[ny][nx] != SPACE && map[ny][x] != '1' && map[y][nx] != '1')
		return true;
	return false;
}

static void up_down(t_mlx *mlx, E_DIRECTION d, int *tmp_x, int *tmp_y)
{
	if (d == UP)
	{
		*tmp_x = mlx->info->player_x + cos(mlx->info->player_angle) * STEP_SIZE;
		*tmp_y = mlx->info->player_y + sin(mlx->info->player_angle) * STEP_SIZE;
	}
	else if (d == DOWN)
	{
		*tmp_x = mlx->info->player_x - cos(mlx->info->player_angle) * STEP_SIZE;
		*tmp_y = mlx->info->player_y - sin(mlx->info->player_angle) * STEP_SIZE;
	}
}

static void right_left(t_mlx *mlx, E_DIRECTION d, int *tmp_x, int *tmp_y)
{
	if (d == RIGHT)
	{
		*tmp_x = mlx->info->player_x + cos(angle_corrector(mlx->info->player_angle + (90 * M_PI) / 180)) * STEP_SIZE;
		*tmp_y = mlx->info->player_y + sin(angle_corrector(mlx->info->player_angle + (90 * M_PI) / 180)) * STEP_SIZE;
	}
	else if (d == LEFT)
	{
		*tmp_x = mlx->info->player_x + cos(angle_corrector(mlx->info->player_angle - (90 * M_PI) / 180)) * STEP_SIZE;
		*tmp_y = mlx->info->player_y + sin(angle_corrector(mlx->info->player_angle - (90 * M_PI) / 180)) * STEP_SIZE;
	}
}

void move(t_mlx *mlx, E_DIRECTION d)
{
	int tmp_y;
	int tmp_x;

	up_down(mlx, d, &tmp_x, &tmp_y);
	right_left(mlx, d, &tmp_x, &tmp_y);
	if (is_gape(mlx->info->arr_map, mlx->info->player_x / SIZE, mlx->info->player_y / SIZE, tmp_x / SIZE, tmp_y / SIZE))
	{
		mlx->info->player_y = tmp_y;
		mlx->info->player_x = tmp_x;
	}
}

void handle_close(void *param)
{
	t_mlx *mlx = (t_mlx *)param;

	mlx_delete_image(mlx->mlx, mlx->r_image);
	mlx_delete_image(mlx->mlx, mlx->map_image);
	mlx_terminate(mlx->mlx);
	free_array(&mlx->info->arr_map);
	free(mlx->info->c_color);
	free(mlx->info->f_color);
	free(mlx->info->east_path);
	free(mlx->info->north_path);
	free(mlx->info->south_path);
	free(mlx->info->west_path);
	free(mlx->info);
	exit(0);
}

void keyhook(mlx_key_data_t keydata, void *param)
{
	t_mlx *mlx = (t_mlx *)param;
	int tmp_y;
	int tmp_x;

	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move(mlx, UP);
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move(mlx, DOWN);
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move(mlx, RIGHT);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		move(mlx, LEFT);
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		// mlx_delete_image(mlx->mlx, mlx->r_image);
		// mlx_delete_image(mlx->mlx, mlx->map_image);
		// mlx_close_hook(mlx->mlx, handle_close, mlx);
		// mlx_close_hook(mlx->mlx, close_window, (void *)mlx);
		exit(0); // i think here some leaks
	}
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		mlx->info->player_angle += (10 * M_PI) / 180.0f;
		mlx->info->player_angle = angle_corrector(mlx->info->player_angle);
	}
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		mlx->info->player_angle -= (10 * M_PI) / 180.0f;
		mlx->info->player_angle = angle_corrector(mlx->info->player_angle);
	}
	else
		return;
	mlx_delete_image(mlx->mlx, mlx->r_image);
	mlx->r_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	display_rays(*mlx);
	display_person(*mlx, mlx->info->player_x, mlx->info->player_y);
	mlx_image_to_window(mlx->mlx, mlx->r_image, 0, 0);
}

void display_window(t_mlx *mlx)
{
	mlx->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	mlx->map_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->r_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	// display_map(*mlx);
	display_rays(*mlx);
	// display_person(*mlx, mlx->info->player_x, mlx->info->player_y);
	mlx_image_to_window(mlx->mlx, mlx->r_image, 0, 0);
	mlx_key_hook(mlx->mlx, keyhook, mlx);
	mlx_close_hook(mlx->mlx, handle_close, mlx);
	mlx_loop(mlx->mlx);
}

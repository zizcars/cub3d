
#include "../includes/types.h"
#include "../includes/parsing.h"

#define FRAME_Y 160
#define FRAME_X 284

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
			mlx_put_pixel(image, (i + x) * FACTOR, (j + y) * FACTOR, color);
			j++;
		}
		i++;
	}
}

void display_person(mlx_image_t *img, const int x, const int y)
{
	float i, j, a;
	i = j = a = 0;
	while (a < 2 * M_PI && i >= 0 && j >= 0)
	{
		i = x + 2.0f * cos(a);
		j = y + 2.0f * sin(a);
		mlx_put_pixel(img, i, j, get_rgba(PERSON_COLOR, 255));
		a += 0.1f;
	}
}

void display_map(t_mlx *mlx)
{
	int x, y;
	int i, j;
	int nx, ny;
	mlx_delete_image(mlx->mlx, mlx->map_image);
	mlx->map_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	y = 0;
	while (y < FRAME_Y)
	{
		x = 0;
		while (x < FRAME_X)
		{
			mlx_put_pixel(mlx->map_image, x, y, get_rgba(SPACE_COLOR, 255));
			x++;
		}
		y++;
	}
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
		j = mlx->info->player_x - FRAME_X / 2;
		x = 0;
		while (x < FRAME_X)
		{
			if (j < 0)
			{
				x++;
				j++;
				continue;
			}
			if (!mlx->info->arr_map[(int)(i / (SIZE))][(int)(j / (SIZE))])
				break;
			if (mlx->info->arr_map[(int)(i / (SIZE))][(int)(j / (SIZE))] == '1')
				mlx_put_pixel(mlx->map_image, x, y, get_rgba(WALL_COLOR, 255));
			else if (mlx->info->arr_map[(int)(i / (SIZE))][(int)(j / (SIZE))] != SPACE)
				mlx_put_pixel(mlx->map_image, x, y, get_rgba(FLOOR_COLOR, 255));
			x++;
			j++;
		}
		i++;
		y++;
	}
	display_person(mlx->map_image, FRAME_X / 2, FRAME_Y / 2);
	mlx_image_to_window(mlx->mlx, mlx->map_image, 0, 0);
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
		exit(0);
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
	display_map(mlx);
}

void mousehook(void *param)
{
	t_mlx *mlx = (t_mlx *)param;
	int x, y;
	static int px;

	mlx_get_mouse_pos(mlx->mlx, &x, &y);
	// printf("x=%d, y=%d\n", x, y);
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT && px != x && (px - x > 10 || px - x < -10))
	{
		if ( px - x > 0)
		{
			mlx->info->player_angle -= (5 * M_PI) / 180.0f;
			mlx->info->player_angle = angle_corrector(mlx->info->player_angle);
		}
		else
		{
			mlx->info->player_angle += (5 * M_PI) / 180.0f;
			mlx->info->player_angle = angle_corrector(mlx->info->player_angle);
		}
		mlx_delete_image(mlx->mlx, mlx->r_image);
		mlx->r_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
		display_rays(*mlx);
		display_map(mlx);
		px = x;
	}
}
void display_window(t_mlx *mlx)
{
	mlx->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	mlx->map_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->r_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx->mlx, mlx->r_image, 0, 0);
	display_rays(*mlx);
	display_map(mlx);
	// display_person(*mlx, mlx->info->player_x, mlx->info->player_y);
	// mlx_mouse_hook(mlx->mlx, mousehook, mlx);
	mlx_key_hook(mlx->mlx, keyhook, mlx);
	mlx_loop_hook(mlx->mlx, mousehook, mlx);
	mlx_close_hook(mlx->mlx, handle_close, mlx);
	mlx_loop(mlx->mlx);
}

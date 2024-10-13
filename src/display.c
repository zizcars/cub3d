
#include "../includes/parsing.h"
#include "../includes/types.h"

#define FRAME_Y 160
#define FRAME_X 284
#define CHECK_N 2

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
			mlx_put_pixel(img, x, y, get_rgba(SPACE_COLOR, 255));
			x++;
		}
		y++;
	}
}
void display_map(t_mlx *mlx)
{
	int x;
	int y;
	int i;
	int j;

	mlx_delete_image(mlx->mlx, mlx->map_image);
	mlx->map_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	// display_mini_map_ground(mlx->map_image);
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
	mlx_put_pixel(mlx->map_image, WIDTH / 2, HEIGHT / 2, get_rgba(255, 0, 0, 255));
	mlx_put_pixel(mlx->map_image, WIDTH / 2 + 1, HEIGHT / 2 + 1, get_rgba(255, 0, 0, 255));
	mlx_put_pixel(mlx->map_image, WIDTH / 2, HEIGHT / 2 + 1, get_rgba(255, 0, 0, 255));
	mlx_put_pixel(mlx->map_image, WIDTH / 2 + 1, HEIGHT / 2, get_rgba(255, 0, 0, 255));
	display_person(mlx->map_image, FRAME_X / 2, FRAME_Y / 2);
	mlx_image_to_window(mlx->mlx, mlx->map_image, 0, 0);
}

double angle_corrector(double angle)
{
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	else if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

static bool is_gape(char **map, int x, int y, int nx, int ny)
{
	// printf("n(%d, %d) o(%d, %d)\n", nx, ny, x, y);
	if (map[ny][nx] != '1' && map[ny][nx] != '\0' && map[ny][nx] != SPACE && map[ny][x] != '1' && map[y][nx] != '1')
		return (true);
	return (false);
}

static void up_down(t_mlx *mlx, E_DIRECTION d, int *tmp_x, int *tmp_y)
{

	if (d == UP)
	{
		// printf("result:%lf\n", round(mlx->info->player_x + cos(mlx->info->player_angle) * STEP_SIZE));
		*tmp_x = round(mlx->info->player_x + cos(mlx->info->player_angle) * STEP_SIZE);
		*tmp_y = round(mlx->info->player_y + sin(mlx->info->player_angle) * STEP_SIZE);
		// printf("Player: (%d, %d) angle:%lf\n", *tmp_x, *tmp_y, mlx->info->player_angle * 180/M_PI);
		if (mlx->info->player_angle <= (3 * M_PI) / 2 && mlx->info->player_angle >= M_PI / 2) // left
		{
			// error_fix = 0;
			mlx->info->check_x = -CHECK_N;
		}
		else
		{
			// error_fix = 1;
			mlx->info->check_x = CHECK_N;
		}
		if (mlx->info->player_angle <= M_PI && mlx->info->player_angle >= 0) // down
			mlx->info->check_y = CHECK_N;
		else
			mlx->info->check_y = -CHECK_N;
	}
	else if (d == DOWN)
	{
		*tmp_x = round(mlx->info->player_x - cos(mlx->info->player_angle) * STEP_SIZE);
		*tmp_y = round(mlx->info->player_y - sin(mlx->info->player_angle) * STEP_SIZE);
		// printf("Player: (%d, %d) angle:%lf\n", *tmp_x, *tmp_y, mlx->info->player_angle * 180/M_PI);
		if (mlx->info->player_angle <= (3 * M_PI) / 2 && mlx->info->player_angle >= M_PI / 2) // left
			mlx->info->check_x = CHECK_N;
		else
			mlx->info->check_x = -CHECK_N;
		if (mlx->info->player_angle <= M_PI && mlx->info->player_angle >= 0) // down
			mlx->info->check_y = -CHECK_N;
		else
			mlx->info->check_y = CHECK_N;
	}
}

static void right_left(t_mlx *mlx, E_DIRECTION d, int *tmp_x, int *tmp_y)
{
	if (d == RIGHT)
	{
		*tmp_x = round(mlx->info->player_x + cos(angle_corrector(mlx->info->player_angle + M_PI_2)) * STEP_SIZE);
		*tmp_y = round(mlx->info->player_y + sin(angle_corrector(mlx->info->player_angle + M_PI_2)) * STEP_SIZE);
		// printf("Player pos: (%d, %d)\n", *tmp_x, *tmp_y);
		if (mlx->info->player_angle <= (3 * M_PI) / 2 && mlx->info->player_angle >= M_PI / 2) // left
			mlx->info->check_y = -CHECK_N;
		else
			mlx->info->check_y = CHECK_N;
		if (mlx->info->player_angle <= M_PI && mlx->info->player_angle >= 0) // down
			mlx->info->check_x = -CHECK_N;
		else
			mlx->info->check_x = CHECK_N;
	}
	else if (d == LEFT)
	{
		*tmp_x = round(mlx->info->player_x + cos(angle_corrector(mlx->info->player_angle - M_PI_2)) * STEP_SIZE);
		*tmp_y = round(mlx->info->player_y + sin(angle_corrector(mlx->info->player_angle - M_PI_2)) * STEP_SIZE);
		// printf("Player pos: (%d, %d)\n", *tmp_x, *tmp_y);
		if (mlx->info->player_angle <= (3 * M_PI) / 2 && mlx->info->player_angle >= M_PI / 2) // left
			mlx->info->check_y = CHECK_N;
		else
			mlx->info->check_y = -CHECK_N;
		if (mlx->info->player_angle <= M_PI && mlx->info->player_angle >= 0) // down
			mlx->info->check_x = CHECK_N;
		else
			mlx->info->check_x = -CHECK_N;
	}
}

void move(t_mlx *mlx, E_DIRECTION d)
{
	int tmp_y;
	int tmp_x;

	up_down(mlx, d, &tmp_x, &tmp_y);
	right_left(mlx, d, &tmp_x, &tmp_y);
	if (is_gape(mlx->info->arr_map, mlx->info->player_x / SIZE, mlx->info->player_y / SIZE, (tmp_x + mlx->info->check_x) / SIZE, (tmp_y + mlx->info->check_y) / SIZE))
	{
		mlx->info->player_y = tmp_y;
		mlx->info->player_x = tmp_x;
	}
}

// void free_info(t_info **info)
// {
// 	free_array(&(*info)->arr_map);
// 	free((*info)->c_color);
// 	free((*info)->f_color);
// 	free((*info)->east_path)
// 	free((*info)->north_path);
// 	free((*info)->south_path);
// 	free((*info)->west_path);
// 	free((*info));
// }

void free_info(t_info *info)
{
	int i;
	i = 0;
	while (i < 4 && info->texture && info->texture[i])
	{
		mlx_delete_texture(info->texture[i]);
		i++;
	}
	free_array(&info->arr_map);
	free(info->c_color);
	free(info->f_color);
	free(info->east_path);
	free(info->north_path);
	free(info->south_path);
	free(info->west_path);
	free(info);
}

void handle_close(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	mlx_delete_image(mlx->mlx, mlx->r_image);
	mlx_delete_image(mlx->mlx, mlx->map_image);
	mlx_delete_image(mlx->mlx, mlx->floor_image);
	mlx_delete_image(mlx->mlx, mlx->minimapfloor_image);
	free_info(mlx->info);
	mlx_terminate(mlx->mlx);
	exit(0);
}

void keyhook(mlx_key_data_t keydata, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
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
		mlx->info->player_angle += (ROTATION_ANGLE * M_PI) / 180.0f;
		mlx->info->player_angle = angle_corrector(mlx->info->player_angle);
	}
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		mlx->info->player_angle -= (ROTATION_ANGLE * M_PI) / 180.0f;
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
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT && px != x && (px - x > 10 || px - x < -10))
	{
		if (px - x > 0)
		{
			mlx->info->player_angle -= (ROTATION_ANGLE * M_PI) / 180.0f;
			mlx->info->player_angle = angle_corrector(mlx->info->player_angle);
		}
		else
		{
			mlx->info->player_angle += (ROTATION_ANGLE * M_PI) / 180.0f;
			mlx->info->player_angle = angle_corrector(mlx->info->player_angle);
		}
		mlx_delete_image(mlx->mlx, mlx->r_image);
		mlx->r_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
		display_rays(*mlx);
		mlx_image_to_window(mlx->mlx, mlx->minimapfloor_image, 0, 0);
		mlx_image_to_window(mlx->mlx, mlx->map_image, 0, 0);
		px = x;
	}
}

void display_window(t_mlx *mlx)
{
	mlx->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	mlx->map_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->floor_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->minimapfloor_image = mlx_new_image(mlx->mlx, FRAME_X, FRAME_Y);
	mlx->r_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx->mlx, mlx->r_image, 0, 0);
	display_mini_map_ground(mlx->minimapfloor_image);
	draw_floor_ceiling(*mlx);
	mlx_image_to_window(mlx->mlx, mlx->floor_image, 0, 0);
	display_rays(*mlx);
	display_map(mlx);
	mlx_key_hook(mlx->mlx, keyhook, mlx);
	mlx_loop_hook(mlx->mlx, mousehook, mlx);
	mlx_close_hook(mlx->mlx, handle_close, mlx);
	mlx_loop(mlx->mlx);
}

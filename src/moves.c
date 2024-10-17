#include "../includes/utiles.h"


static void move_up(t_mlx *mlx, int *tmp_x, int *tmp_y)
{
	*tmp_x = round(mlx->info->player_x + cos(mlx->info->player_angle) * STEP_SIZE);
	*tmp_y = round(mlx->info->player_y + sin(mlx->info->player_angle) * STEP_SIZE);
	if (mlx->info->player_angle <= (3 * M_PI) / 2 && mlx->info->player_angle >= M_PI / 2) // left
		mlx->info->check_x = -CHECK_N;
	else
		mlx->info->check_x = CHECK_N;
	if (mlx->info->player_angle <= M_PI && mlx->info->player_angle >= 0) // down
		mlx->info->check_y = CHECK_N;
	else
		mlx->info->check_y = -CHECK_N;
}

static void move_down(t_mlx *mlx, int *tmp_x, int *tmp_y)
{
	*tmp_x = round(mlx->info->player_x - cos(mlx->info->player_angle) * STEP_SIZE);
	*tmp_y = round(mlx->info->player_y - sin(mlx->info->player_angle) * STEP_SIZE);
	if (mlx->info->player_angle <= (3 * M_PI) / 2 && mlx->info->player_angle >= M_PI / 2) // left
		mlx->info->check_x = CHECK_N;
	else
		mlx->info->check_x = -CHECK_N;
	if (mlx->info->player_angle <= M_PI && mlx->info->player_angle >= 0) // down
		mlx->info->check_y = -CHECK_N;
	else
		mlx->info->check_y = CHECK_N;
}

static void move_right(t_mlx *mlx, int *tmp_x, int *tmp_y)
{

	*tmp_x = round(mlx->info->player_x + cos(angle_corrector(mlx->info->player_angle + M_PI_2)) * STEP_SIZE);
	*tmp_y = round(mlx->info->player_y + sin(angle_corrector(mlx->info->player_angle + M_PI_2)) * STEP_SIZE);
	if (mlx->info->player_angle <= (3 * M_PI) / 2 && mlx->info->player_angle >= M_PI / 2) // left
		mlx->info->check_y = -CHECK_N;
	else
		mlx->info->check_y = CHECK_N;
	if (mlx->info->player_angle <= M_PI && mlx->info->player_angle >= 0) // down
		mlx->info->check_x = -CHECK_N;
	else
		mlx->info->check_x = CHECK_N;
}

static void move_left(t_mlx *mlx, int *tmp_x, int *tmp_y)
{
	*tmp_x = round(mlx->info->player_x + cos(angle_corrector(mlx->info->player_angle - M_PI_2)) * STEP_SIZE);
	*tmp_y = round(mlx->info->player_y + sin(angle_corrector(mlx->info->player_angle - M_PI_2)) * STEP_SIZE);
	if (mlx->info->player_angle <= (3 * M_PI) / 2 && mlx->info->player_angle >= M_PI / 2) // left
		mlx->info->check_y = CHECK_N;
	else
		mlx->info->check_y = -CHECK_N;
	if (mlx->info->player_angle <= M_PI && mlx->info->player_angle >= 0) // down
		mlx->info->check_x = CHECK_N;
	else
		mlx->info->check_x = -CHECK_N;
}

static bool is_gape(char **map, int x, int y, int nx, int ny)
{
	if (map[ny][nx] != '1' && map[ny][nx] != '\0' && map[ny][nx] != SPACE \
		&& map[ny][x] != '1' && map[y][nx] != '1')
		return (true);
	return (false);
}

void move(t_mlx *mlx, E_DIRECTION d)
{
	int tmp_y;
	int tmp_x;

	tmp_y = 0;
	tmp_x = 0;
	if (d == UP)
		move_up(mlx, &tmp_x, &tmp_y);
	else if (d == DOWN)
		move_down(mlx, &tmp_x, &tmp_y);
	else if (d == RIGHT)
		move_right(mlx, &tmp_x, &tmp_y);
	else if (d == LEFT)
		move_left(mlx, &tmp_x, &tmp_y);
	if (is_gape(mlx->info->arr_map, mlx->info->player_x / SIZE, mlx->info->player_y / SIZE, (tmp_x + mlx->info->check_x) / SIZE, (tmp_y + mlx->info->check_y) / SIZE))
	{
		mlx->info->player_y = tmp_y;
		mlx->info->player_x = tmp_x;
	}
}

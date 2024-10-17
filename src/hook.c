#include "../includes/utiles.h"

static void update_map(t_mlx *mlx)
{
	mlx_delete_image(mlx->mlx, mlx->r_image);
	mlx->r_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	display_rays(*mlx);
	display_map(mlx);
}

static void rotation_right(double *player_angle)
{
	*player_angle += (ROTATION_ANGLE * M_PI) / 180.0f;
	*player_angle = angle_corrector(*player_angle);
}

static void rotation_left(double *player_angle)
{
	*player_angle -= (ROTATION_ANGLE * M_PI) / 180.0f;
	*player_angle = angle_corrector(*player_angle);
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
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		rotation_right(&mlx->info->player_angle);
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		rotation_left(&mlx->info->player_angle);
	else if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	else
		return;
	update_map(mlx);
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

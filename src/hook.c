#include "../includes/utiles.h"

void update_map(t_mlx *mlx)
{
	mlx_delete_image(mlx->mlx, mlx->r_image);
	mlx->r_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	draw_floor_ceiling(*mlx);
	display_rays(*mlx);
	display_mini_map_ground(mlx->r_image);
	display_mini_map(mlx);
	mlx_image_to_window(mlx->mlx, mlx->r_image, 0, 0);
}

static void rotation_right(double *player_angle, t_mlx *mlx)
{
	*player_angle += (ROTATION_ANGLE * M_PI) / 180.0f;
	*player_angle = angle_corrector(*player_angle);
}

static void rotation_left(double *player_angle, t_mlx *mlx)
{
	*player_angle -= (ROTATION_ANGLE * M_PI) / 180.0f;
	*player_angle = angle_corrector(*player_angle);
}

void keyhook(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;	
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_W))
		move(mlx, UP);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_S))
		move(mlx, DOWN);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_D))
		move(mlx, RIGHT);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_A))
		move(mlx, LEFT);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
		rotation_right(&mlx->info->player_angle, mlx);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
		rotation_left(&mlx->info->player_angle, mlx);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
		exit(0);
	update_map(mlx);
}

void mousehook(void *param)
{
	t_mlx *mlx;
	int x;
	int y;
	static int px;

	mlx = (t_mlx *)param;
	mlx_get_mouse_pos(mlx->mlx, &x, &y);
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT && px != x && (px - x > MOUSE_R || px - x < -MOUSE_R))
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
		px = x;
	}
}

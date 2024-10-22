
#include "../includes/utiles.h"

double angle_corrector(double angle)
{
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	else if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

void free_info(t_info *info)
{
	int i;
	i = 0;
	while (i < 4 && info->texture[i])
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

void display_window(t_mlx *mlx)
{
	mlx->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	mlx->map_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->floor_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->minimapfloor_image = mlx_new_image(mlx->mlx, FRAME_X, FRAME_Y);
	mlx->r_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	// mlx_image_to_window(mlx->mlx, mlx->r_image, 0, 0);
	draw_floor_ceiling(*mlx);
	mlx_image_to_window(mlx->mlx, mlx->floor_image, 0, 0);
	display_rays(*mlx);
	display_mini_map_ground(mlx->minimapfloor_image);
	display_map(mlx);
	mlx_loop_hook(mlx->mlx, keyhook, mlx);
	mlx_loop_hook(mlx->mlx, mousehook, mlx);
	mlx_close_hook(mlx->mlx, handle_close, mlx);
	mlx_loop(mlx->mlx);
}

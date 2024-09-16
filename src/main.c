
#include "../includes/parsing.h"

void print_info(t_info *info)
{
	printf("North path: %s\n", info->north_path);
	printf("South path: %s\n", info->south_path);
	printf("West path: %s\n", info->west_path);
	printf("East path: %s\n", info->east_path);
	printf("Floor color: %s\n", info->floor_color);
	printf("Ceiling color: %s\n", info->ceiling_color);
	printf("Floor color: [%d, %d, %d]\n", info->f_color[0], info->f_color[1], info->f_color[2]);
	printf("Ceiling color: [%d, %d, %d]\n", info->c_color[0], info->c_color[1], info->c_color[2]);
	printf("width: %d\t heigth: %d\n", info->width, info->height);
	printf("Player:(%d,%d)\n", info->x_player, info->y_player);
	printf("MAP: \n");
	for (int i = 0; info->arr_map[i]; i++)
	{
		printf("|%s|\n", info->arr_map[i]);
	}
}

// solve the problem of space between i information like F 32,   34, 343
// check the number of players and other characters in the map

void put_pixel(t_mlx *mlx, int x, int y, int color)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			mlx_put_pixel(mlx->image, x + i, y + j, color);
	}
	mlx_image_to_window(mlx->mlx, mlx->image, 0, 0);
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
			// printf("%c\n", info->arr_map[i][j]);
			if (mlx.info->arr_map[i][j] == '1')
				display_square(mlx, get_rgba(0, 0, 0, 500), x, y);
			// else if (info->arr_map[i][j] == '0')
			// 	display_square(mlx, get_rgba(255, 255, 255, 255), x, y);
			else
				display_square(mlx, get_rgba(255, 255, 255, 255), x, y);
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

	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (mlx->info->y_player - 5 > 0)
			mlx->info->y_player -= 5;
	}
	else if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (mlx->info->y_player + 5 < mlx->info->height * SIZE)
			mlx->info->y_player += 5;
	}
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (mlx->info->x_player + 5 < mlx->info->width * SIZE)
			mlx->info->x_player += 5;
	}
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (mlx->info->x_player - 5 >= 0)
			mlx->info->x_player -= 5;
	}
	else
		return;
	printf("x: %d| y: %d| width: %d| height: %d\n", mlx->info->x_player, mlx->info->y_player, mlx->info->width * SIZE, mlx->info->height * SIZE);
	// mlx_delete_image(mlx->mlx, mlx->p_image);
	mlx->image = mlx_new_image(mlx->mlx, mlx->width * SIZE, mlx->height * SIZE);
	display_map(*mlx);
	// printf("hi\n");
	put_pixel(mlx, mlx->info->x_player, mlx->info->y_player, get_rgba(0, 255, 0, 255));
}

int main()
{
	// t_info *info;
	int fd;
	t_mlx mlx;
	int color_;

	fd = open("maps/map1.cub", O_RDONLY);
	if (fd < 0)
		printf("no file\n");
	mlx.info = read_info(fd);
	// print_info(info);
	close(fd);
	color_ = get_rgba(200, 35, 12, 255);
	mlx.mlx = mlx_init(mlx.info->width * SIZE, mlx.info->height * SIZE, "test", true);
	mlx.image = mlx_new_image(mlx.mlx, mlx.info->width * SIZE, mlx.info->height * SIZE);
	display_map(mlx);
	put_pixel(&mlx, mlx.info->x_player * SIZE, mlx.info->y_player * SIZE, get_rgba(0, 255, 0, 255));
	mlx_image_to_window(mlx.mlx, mlx.image, 0, 0);
	mlx_key_hook(mlx.mlx, keyhook, &mlx);
	mlx_loop(mlx.mlx);
}
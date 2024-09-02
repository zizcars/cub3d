
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
	printf("MAP: \n");
	for (int i = 0; info->arr_map[i]; i++)
	{
		printf("|%s|\n", info->arr_map[i]);
	}
	printf("width: %d\t heigth: %d\n", info->width, info->height);
}

// solve the problem of space between i information like F 32,   34, 343
// check the number of players and other characters in the map



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

void display_map(t_mlx mlx, t_info *info)
{
	int i;
	int j;
	int x;
	int y = 0;
	i = 0;
	while (info->arr_map[i])
	{
		j = 0;
		x = 0;
		while (info->arr_map[i][j])
		{
			// printf("%c\n", info->arr_map[i][j]);
			if (info->arr_map[i][j] == '1')
				display_square(mlx, get_rgba(0, 0, 0, 500), x, y);
			else if (info->arr_map[i][j] == '0')
				display_square(mlx, get_rgba(255, 255, 255, 255), x, y);
			else
				display_square(mlx, get_rgba(0, 255, 0, 255), x, y);
			j++;
			x += SIZE;
		}
		y += SIZE;
		i++;
	}
}

int main()
{
	t_info *info;
	int fd;

	fd = open("maps/map1.cub", O_RDONLY);
	if (fd < 0)
		printf("no file\n");
	info = read_info(fd);
	// print_info(info);
	close(fd);
	int color;
	t_mlx mlx;
	color = get_rgba(200, 35, 12, 255);
	mlx.mlx = mlx_init(info->width * SIZE, info->height * SIZE, "test", true);
	mlx.image = mlx_new_image(mlx.mlx, info->width * SIZE, info->height * SIZE);
	display_map(mlx, info);
	mlx_image_to_window(mlx.mlx, mlx.image, 0, 0);
	mlx_loop(mlx.mlx);
}
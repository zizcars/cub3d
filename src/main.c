
#include "../includes/parsing.h"

void print_info(t_info *info)
{
	if (info)
	{
		printf("North path: %s\n", info->north_path);
		printf("South path: %s\n", info->south_path);
		printf("West path: %s\n", info->west_path);
		printf("East path: %s\n", info->east_path);
		if (info->c_color)
			printf("Ceiling color: [%d, %d, %d]\n", info->c_color[0], info->c_color[1], info->c_color[2]);
		else
			printf("Ceiling color: (null)\n");
		if (info->f_color)
			printf("Floor color: [%d, %d, %d]\n", info->f_color[0], info->f_color[1], info->f_color[2]);
		else
			printf("Floor color: (null)\n");
		printf("width: %d\t heigth: %d\n", info->width, info->height);
		printf("Player:(%d,%d)\n", info->player_x, info->player_y);
		if (info->arr_map)
		{
			printf("MAP: \n");
			for (int i = 0; info->arr_map[i]; i++)
			{
				printf("|%s|\n", info->arr_map[i]);
			}
		}
		else
			printf("map:(null)\n");
	}
	else
		printf("info: (null)\n");
}

int main()
{
	int fd;
	t_mlx mlx;

	fd = open("maps/test.cub", O_RDONLY);
	if (fd < 0)
		printf("no file\n");
	mlx.info = read_info(fd);
	print_info(mlx.info);
	close(fd);
	// display_window(&mlx);
	// system("leaks -q cub3D");
}

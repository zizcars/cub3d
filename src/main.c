
#include "../includes/parsing.h"

void print_info(t_info *info)
{
	printf("North path: %s\n", info->north_path);
	printf("South path: %s\n", info->south_path);
	printf("West path: %s\n", info->west_path);
	printf("East path: %s\n", info->east_path);
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


int main()
{
	int fd;
	t_mlx mlx;

	fd = open("maps/map.cub", O_RDONLY);
	if (fd < 0)
		printf("no file\n");
	mlx.info = read_info(fd);
	// print_info(info);
	close(fd);
	display_window(&mlx);
}
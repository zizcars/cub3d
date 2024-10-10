
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
				printf("|%s|\n", info->arr_map[i]);
		}
		else
			printf("map:(null)\n");
	}
	else
		printf("info: (null)\n");
}

void leaks()
{
	system("leaks -q cub3D");
}


// You should display emty spaces before 0s and 1s
int main(int ac, char **av)
{
	int fd;
	t_mlx mlx;

	atexit(leaks);
	if (ac == 2)
	{
		if (check_filename(av[1]) == false)
			ft_error("Invalid filetype: *.cub");
		fd = open(av[1], O_RDWR);
		if (fd < 0)
			ft_error("no file");
		mlx.info = read_info(fd);
		// print_info(mlx.info);
		if (!mlx.info)
			return ft_error("error on elements"), 1;
		close(fd);
		display_window(&mlx);
	}
	else
		ft_error("./cub3d A path for map");
}

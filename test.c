
// bool check_map(char *row)
// {
// 	int i;
// 	int player_count;
// 	player_count = 0;
// 	i = 0;
// 	while (row && row[i] != '\n')
// 	{
// 		if (row[i] != '1')
// 		{
// 			printf("false 1:|%c|\n", row[i]);
// 			return (false);
// 		}
// 		i++;
// 	}
// 	while (row && row[i])
// 	{
// 		if (row[i] == '\n' && row[i + 1] && row[i + 1] != '1')
// 		{
// 			printf("false 4\n");
// 			return (false);
// 		}
// 		if (row[i] == '\n')
// 		{
// 			if (row[i + 1] == '\n')
// 				return (false);
// 			i++;
// 			continue;
// 		}
// 		if (check_char(row[i]) == false)
// 		{
// 			printf("false 2\n");
// 			return (false);
// 		}
// 		if (row[i] != '1' && row[i + 1] && row[i + 1] == '\n')
// 		{
// 			printf("false 3\n");
// 			return (false);
// 		}
// 		if (row[i] == 'N' || row[i] == 'S' || row[i] == 'E' || row[i] == 'W')
// 			player_count++;
// 		if (player_count > 1)
// 			return (false);
// 		i++;
// 	}
// 	if (player_count != 1)
// 		return (false);
// 	i -= 2;
// 	while (i > 0 && row[i] != '\n')
// 	{
// 		if (row[i] != '1')
// 		{
// 			printf("false 5:|%c|\n", row[i]);
// 			return (false);
// 		}
// 		i--;
// 	}
// 	return (true);
// }


// Written by Bruh

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "libs/libft/libft.h"
#include "libs/MLX42/include/MLX42/MLX42.h"
#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
// static void ft_error(void)
// {
// 	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

// Print the window width and height.
// static void ft_hook(void* param)
// {
// 	const mlx_t* mlx = param;

// 	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
// }

// int32_t	main(void)
// {

// 	// MLX allows you to define its core behaviour before startup.
// 	mlx_set_setting(MLX_MAXIMIZED, true);
// 	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
// 	if (!mlx)
// 		ft_error();

// 	/* Do stuff */

// 	// Create and display the image.
// 	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
// 	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
// 		ft_error();

// 	// Even after the image is being displayed, we can still modify the buffer.
// 	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

// 	// Register a hook and pass mlx as an optional param.
// 	// NOTE: Do this before calling mlx_loop!
// 	mlx_loop_hook(mlx, ft_hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }

void ft_error(char *error_ms)
{
	write(STDERR_FILENO, error_ms, strlen(error_ms));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

int check_ones(char *line)
{
	int i;
	bool is_one;

	is_one = false;
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] == '1')
	{
		is_one = true;
		i++;
	}
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '\0' || is_one == false)
		ft_error("The map not srounded by walls");
	return i;
}

int main()
{
	char *line = "11111111";
	check_ones(line);
	printf("Every thing is good \n");
}
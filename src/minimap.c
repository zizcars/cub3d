/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:30:15 by achakkaf          #+#    #+#             */
/*   Updated: 2024/10/28 11:27:51 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

static void	increment(int *x, int *j)
{
	(*x)++;
	(*j)++;
}

void	draw_map(t_mlx mlx, int y, int i)
{
	int	j;
	int	x;

	j = mlx.info->player_x - FRAME_X / 2;
	x = 0;
	while (x < FRAME_X)
	{
		if (j < 0)
		{
			increment(&x, &j);
			continue ;
		}
		if (mlx.info->map[i / SIZE] && \
			(int)ft_strlen(mlx.info->map[i / SIZE]) > j / SIZE)
		{
			if (!mlx.info->map[i / SIZE][j / SIZE])
				break ;
			if (mlx.info->map[i / SIZE][j / SIZE] == '1')
				mlx_put_pixel(mlx.r_image, x, y, get_rgba(1, 22, 30, 255));
			else if (mlx.info->map[i / SIZE][j / SIZE] != SPACE)
				mlx_put_pixel(mlx.r_image, x, y, get_rgba(239, 246, 224, 255));
		}
		increment(&x, &j);
	}
}

void	draw_point(mlx_image_t *img, int x, int y)
{
	mlx_put_pixel(img, x, y, get_rgba(0, 255, 0, 255));
	mlx_put_pixel(img, x, y + 1, get_rgba(0, 255, 0, 255));
	mlx_put_pixel(img, x + 1, y, get_rgba(0, 255, 0, 255));
	mlx_put_pixel(img, x + 1, y + 1, get_rgba(0, 255, 0, 255));
}

void	draw_focus_point(mlx_image_t *img)
{
	int	i;

	draw_point(img, WIDTH / 2, HEIGHT / 2);
	i = 6;
	while (i < 10)
		draw_point(img, WIDTH / 2 + i++, HEIGHT / 2);
	i = 6;
	while (i < 10)
		draw_point(img, WIDTH / 2 - i++, HEIGHT / 2);
	i = 6;
	while (i < 10)
		draw_point(img, WIDTH / 2, HEIGHT / 2 + i++);
	i = 6;
	while (i < 10)
		draw_point(img, WIDTH / 2, HEIGHT / 2 - i++);
}

void	display_mini_map(t_mlx *mlx)
{
	int	y;
	int	i;

	i = mlx->info->player_y - FRAME_Y / 2;
	y = 0;
	while (y < FRAME_Y)
	{
		if (i < 0)
		{
			i++;
			y++;
			continue ;
		}
		if (!mlx->info->map[i / SIZE])
			break ;
		draw_map(*mlx, y, i);
		i++;
		y++;
	}
	draw_focus_point(mlx->r_image);
	display_person(mlx->r_image, FRAME_X / 2, FRAME_Y / 2);
}

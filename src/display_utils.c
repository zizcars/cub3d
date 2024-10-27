/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:45:46 by achakkaf          #+#    #+#             */
/*   Updated: 2024/10/27 14:46:31 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

void	put_pixel(mlx_image_t *image, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			mlx_put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	display_square(mlx_image_t *image, int color, const int x, const int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			mlx_put_pixel(image, (i + x) * FACTOR, (j + y) * FACTOR, color);
			j++;
		}
		i++;
	}
}

void	display_person(mlx_image_t *img, const int x, const int y)
{
	double	i;
	double	j;
	double	a;

	i = 0;
	j = 0;
	a = 0;
	while (a < 2 * M_PI && i >= 0 && j >= 0)
	{
		i = x + 2.0f * cos(a);
		j = y + 2.0f * sin(a);
		mlx_put_pixel(img, i, j, get_rgba(PERSON_COLOR));
		a += 0.1f;
	}
}

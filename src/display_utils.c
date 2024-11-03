/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:45:46 by achakkaf          #+#    #+#             */
/*   Updated: 2024/11/03 09:51:31 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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
		mlx_put_pixel(img, i, j, get_rgba(174, 195, 176, 255));
		a += 0.1f;
	}
}

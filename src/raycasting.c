/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:36:41 by abounab           #+#    #+#             */
/*   Updated: 2024/10/28 11:28:14 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

void	draw_floor_ceiling(t_mlx mlx)
{
	uint32_t	color;
	int			y;
	int			x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				color = get_rgba(mlx.info->c_color[0], \
					mlx.info->c_color[1], mlx.info->c_color[2], 255);
			else
				color = get_rgba(mlx.info->f_color[0], \
					mlx.info->f_color[1], mlx.info->f_color[2], 255);
			mlx_put_pixel(mlx.r_image, x, y, color);
			x++;
		}
		y++;
	}
}

int	get_color(mlx_texture_t *texture, int x, int y)
{
	uint8_t	*pos;
	int		p;
	int		color;

	p = (y * texture->width * 4) + (x * 4);
	if (x < 0 || y < 0 || p >= (int)(texture->width * \
		texture->bytes_per_pixel * texture->height))
		return (0);
	pos = (&texture->pixels[p]);
	color = (pos[0] << 24 | pos[1] << 16 | pos[2] << 8 | pos[3]);
	return (color);
}

void	rays_utils(t_mlx mlx, double angle, double start_angle, int r)
{
	t_point	*a;
	t_point	*b;

	angle = angle_corrector(start_angle + r * PLAYER_FOV / NUM_RAYS);
	a = calculate_horizontal_intersection(mlx, angle);
	b = calculate_vertical_intersection(mlx, angle);
	b->vertical = true;
	a->angle = angle;
	b->angle = angle;
	a->ray = r;
	b->ray = r;
	if (a->x > 0 && a->x < mlx.info->width * SIZE && a->y > 0 \
		&& a->y < mlx.info->height * SIZE && a->distance < b->distance)
		render3d(mlx, a);
	else if (b->x > 0 && b->x < mlx.info->width * SIZE && b->y > 0 \
			&& b->y < mlx.info->height * SIZE && a->distance >= b->distance)
		render3d(mlx, b);
	free(a);
	free(b);
}

void	display_rays(t_mlx mlx)
{
	double	start_angle;
	double	angle;
	int		r;

	start_angle = angle_corrector(mlx.info->player_angle - PLAYER_FOV / 2.0f);
	angle = start_angle;
	r = 0;
	while (r < NUM_RAYS)
	{
		rays_utils(mlx, angle, start_angle, r);
		r++;
	}
}

void	display_mini_map_ground(mlx_image_t *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < FRAME_Y)
	{
		x = 0;
		while (x < FRAME_X)
		{
			mlx_put_pixel(img, x, y, get_rgba(18, 69, 89, 255));
			x++;
		}
		y++;
	}
}

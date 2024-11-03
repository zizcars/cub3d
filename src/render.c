/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:35:58 by achakkaf          #+#    #+#             */
/*   Updated: 2024/11/03 15:58:57 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

double	calculate_wall_h(t_mlx mlx, t_point *x)
{
	double	prep_distance;
	double	wall_h;

	prep_distance = x->distance * cos(x->angle - mlx.info->player_angle);
	wall_h = (BOX / prep_distance) * ((WIDTH / 2) / (tan(PLAYER_FOV / 2)));
	return (wall_h);
}

void	calculate_start_end(t_render *render)
{
	render->start_pix = -(render->wall_h / 2) + (HEIGHT / 2);
	render->end_pix = (render->wall_h / 2) + (HEIGHT / 2);
	if (render->end_pix > HEIGHT)
		render->end_pix = HEIGHT;
	if (render->start_pix < 0)
		render->start_pix = 0;
}

void	calculate_texture_x(t_mlx mlx, t_point *x, t_render *render)
{
	if (!x->vertical)
	{
		render->r = 2;
		if (x->angle <= M_PI && x->angle >= 0)
			render->r = 1;
		render->texture_off_set_x 
			= (int) fmodf((x->x * mlx.info->texture[render->r]->width / BOX),
				mlx.info->texture[render->r]->width);
	}
	else
	{
		render->r = 0;
		if (x->angle <= (3 * M_PI) / 2 && x->angle >= M_PI / 2)
			render->r = 3;
		render->texture_off_set_x 
			= (int) fmodf((x->y * mlx.info->texture[render->r]->width / BOX),
				mlx.info->texture[render->r]->width);
	}
}

void	render3d(t_mlx mlx, t_point *x)
{
	t_render	render;
	int			y;
	int			differencetop;
	int			color;

	render.wall_h = calculate_wall_h(mlx, x);
	calculate_start_end(&render);
	calculate_texture_x(mlx, x, &render);
	y = render.start_pix;
	while (y < render.end_pix)
	{
		differencetop = (y + render.wall_h / 2 - HEIGHT / 2);
		render.texture_off_set_y = differencetop * \
			(mlx.info->texture[render.r]->height / render.wall_h);
		color = get_color(mlx.info->texture[render.r], \
			render.texture_off_set_x, render.texture_off_set_y);
		mlx_put_pixel(mlx.r_image, x->ray, y, color);
		y++;
	}
}

bool	move_check(t_mlx mlx, int nx, int ny)
{
	if (mlx.info->map[ny][nx] != '1' && mlx.info->map[ny][nx] != '\0')
		if (mlx.info->map[ny][nx] != SPACE)
			if (mlx.info->map[ny][mlx.info->player_x / SIZE] != '1' && \
				mlx.info->map[mlx.info->player_y / SIZE][nx] != '1')
				return (true);
	return (false);
}

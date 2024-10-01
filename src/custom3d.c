/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:14:58 by abounab           #+#    #+#             */
/*   Updated: 2024/10/01 19:12:28 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/types.h"
#include "../includes/parsing.h"

double	get_x_o(mlx_texture_t *texture, t_config *mlx)
{
	double	x_o;

	if (mlx->ray.flag == 1)
		x_o = (int)fmodf((mlx->ray.horiz_x * (texture->width / TILE_SIZE)),
				texture->width);
	else
		x_o = (int)fmodf((mlx->ray.vert_y * (texture->width / TILE_SIZE)),
				texture->width);
	return (x_o);
}

void	draw_wall(t_config *mlx, double top_pix, double min_pix, double wall_h)
{
	double			x_o;
	double			y_o = 0;
	uint32_t		*arr;
	double			y_step;
	mlx_texture_t	*texture;
	
	// getting texture
	texture = get_texture_bonus(mlx, mlx->ray.flag);
	if (!texture)
		return ;
	// turning it into an array
	arr = (uint32_t *)texture->pixels;
	// getting steps
	y_step = (double)texture->height / wall_h;
	// scale x corfination
	x_o = get_x_o(texture, mlx);
	// scale y cordination
	y_o = (top_pix - (mlx->height_window / 2) + (wall_h / 2)) * y_step;
	// never negative for the height
	if (y_o < 0)
		y_o = 0;
	// looping from the top pix to the min pix 
	while (top_pix < min_pix)
	{
		mlx_put_pixel(mlx->img, mlx->ray.index, top_pix, reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += y_step;
		top_pix++;
	}
}

void	render_wall(t_config **data, int ray, double distance, double angle)
{
	double wall_h;
	double min_pix;
	double top_pix;
	(void)angle;
	
// initialise ray.index : ray.index 
	(*data)->ray.index = ray;
	// update distance to avoid fish eye : player.angle, mouvmt of camera left
	distance *= cos(normalizeAngle(angle - ((*data)->player.angle
					+ (*data)->mouv_camera_left)));
	// initialise ray.distance
	(*data)->ray.distance = distance;
	// get value of wall height : size , width , player fov rd
	wall_h = ((*data)->size / distance) * (((*data)->width_window / 2) / tan((*data)->player.fov_rd / 2));
	// get value of the bottom pix : height window
	min_pix = ((*data)->height_window / 2) + (wall_h / 2);                                                
	// get value of the top pix : height window
	top_pix = ((*data)->height_window / 2) - (wall_h / 2);                                                
	// change bottom pix for a smaller height : height window
	if (min_pix > (*data)->height_window)                                                                
		min_pix = (*data)->height_window;
	// top pixel always positive
	if (top_pix < 0)
		top_pix = 0;
	// drawing floor and ceiling : iwould color all the middle by a color and all other middle by another and them draw walls above them
	draw_floor_ceiling(*data, ray, top_pix, min_pix);
	// drawing walls
	draw_wall(*data, top_pix, min_pix, wall_h);
}

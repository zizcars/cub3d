/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:36:41 by abounab           #+#    #+#             */
/*   Updated: 2024/10/22 15:40:02 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

static bool is_gape(char **map, int x, int y, int nx, int ny)
{
	if ((int)ft_strlen(map[ny]) > nx && (map[ny][nx] == '1' || map[ny][nx] == '\0' || map[ny][nx] == SPACE))
		return true;
	else if ((int)ft_strlen(map[y]) > nx && (int)ft_strlen(map[ny]) > x && map[ny][x] == '1' && map[y][nx] == '1')
		return true;
	return false;
}

static void find_horizontal_intersection(t_mlx mlx, double angle, t_point *a)
{
	double x;
	double y;
	double tx;
	double ty;

	tx = a->x;
	ty = a->y;
	while (a->x > 0 && a->x < mlx.info->width * SIZE && a->y > 0 && a->y < mlx.info->height * SIZE)
	{
		if (is_gape(mlx.info->arr_map, tx / SIZE, ty / SIZE, a->x / SIZE, a->y / SIZE))
			break;
		if (angle <= M_PI && angle >= 0) // down
			y = SIZE;
		else
			y = -SIZE;
		x = y / tan(angle);
		tx = a->x;
		ty = a->y;
		a->x += x;
		a->y += y;
	}
}

t_point *calculate_horizontal_intersection(t_mlx mlx, double angle)
{
	t_point *a;

	a = ft_calloc(1, sizeof(t_point));
	if (a == NULL)
		ft_error("malloc faild");
	if (angle <= M_PI && angle >= 0)
		a->y = floor(mlx.info->player_y / SIZE) * SIZE + SIZE;
	else
		a->y = floor(mlx.info->player_y / SIZE) * SIZE - 0.00001;
	a->x = (a->y - mlx.info->player_y) / tan(angle) + mlx.info->player_x;
	find_horizontal_intersection(mlx, angle, a);
	if (a->x > 0 && a->x < mlx.info->width * SIZE && a->y > 0 && a->y < mlx.info->height * SIZE)
		a->distance = sqrt(pow(mlx.info->player_x - a->x, 2) + pow(mlx.info->player_y - a->y, 2));
	else
		a->distance = 2147483647;
	return a;
}

static void find_vertical_intersection(t_mlx mlx, const double angle, t_point *a)
{
	double x;
	double y;
	double tx;
	double ty;

	tx = a->x;
	ty = a->y;
	while (a->x > 0 && a->x < mlx.info->width * SIZE && a->y > 0 && a->y < mlx.info->height * SIZE)
	{
		if (is_gape(mlx.info->arr_map, tx / SIZE, ty / SIZE, a->x / SIZE, a->y / SIZE))
			break;
		if (angle <= (3 * M_PI) / 2 && angle >= M_PI / 2) // left
			x = -SIZE;
		else
			x = SIZE;
		y = x * tan(angle);
		tx = a->x;
		ty = a->y;
		a->x += x;
		a->y += y;
	}
}

t_point *calculate_vertical_intersection(t_mlx mlx, const double angle)
{
	t_point *a;

	a = ft_calloc(1, sizeof(t_point));
	if (a == NULL)
		ft_error("malloc faild");
	if (angle <= (3 * M_PI) / 2 && angle >= M_PI / 2) // left
		a->x = (mlx.info->player_x / SIZE) * SIZE - 0.00001;
	else
		a->x = (mlx.info->player_x / SIZE) * SIZE + SIZE;
	a->y = mlx.info->player_y + (a->x - mlx.info->player_x) * tan(angle);
	find_vertical_intersection(mlx, angle, a);
	if (a->x > 0 && a->x < mlx.info->width * SIZE && a->y > 0 && a->y < mlx.info->height * SIZE)
		a->distance = sqrt(pow(mlx.info->player_x - a->x, 2) + pow(mlx.info->player_y - a->y, 2));
	else
		a->distance = 2147483647;
	return a;
}

void draw_floor_ceiling(t_mlx mlx)
{
	uint32_t color;
	int y;
	int x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				color = get_rgba(mlx.info->c_color[0], mlx.info->c_color[1], mlx.info->c_color[2], 255);
			else
				color = get_rgba(mlx.info->f_color[0], mlx.info->f_color[1], mlx.info->f_color[2], 255);
			mlx_put_pixel(mlx.r_image, x, y, color);
			x++;
		}
		y++;
	}
}

int get_color(mlx_texture_t *texture, int x, int y)
{
	uint8_t *pos;
	int p;
	int color;

	p = (y * texture->width * 4) + (x * 4);
	if (x < 0 || y < 0 || p >= (int)(texture->width * texture->bytes_per_pixel * texture->height))
		return (0);
	pos = (&texture->pixels[p]);
	color = (pos[0] << 24 | pos[1] << 16 | pos[2] << 8 | pos[3]);
	return (color);
}

void render3d(t_mlx mlx, t_point *x)
{
	int textureOffsetX;
	int textureOffsetY;

	double prep_distance;
	double wall_h;

	double start_pix;
	double end_pix;

	int r;
	int y;
	prep_distance = x->distance * cos(x->angle - mlx.info->player_angle);
	wall_h = (BOX / prep_distance) * ((WIDTH / 2) / (tan(PLAYER_FOV / 2)));

	start_pix = -(wall_h / 2) + (HEIGHT / 2);
	end_pix = (wall_h / 2) + (HEIGHT / 2);
	if (end_pix > HEIGHT)
		end_pix = HEIGHT;
	if (start_pix < 0)
		start_pix = 0;

	if (!x->vertical)
	{
		r = 2;
		if (x->angle <= M_PI && x->angle >= 0)
			r = 1;
		textureOffsetX = ((x->x / BOX) - floor(x->x / BOX)) * mlx.info->texture[r]->width;
	}
	else
	{
		r = 0;
		if (x->angle <= (3 * M_PI) / 2 && x->angle >= M_PI / 2)
			r = 3;
		textureOffsetX = ((x->y / BOX) - floor(x->y / BOX)) * mlx.info->texture[r]->width;
	}

	y = start_pix;
	while (y < end_pix)
	{
		// assignment in norminette
		int differencetop = (y + wall_h / 2 - HEIGHT / 2);
		textureOffsetY = differencetop * (mlx.info->texture[r]->height / wall_h);
		int color = get_color(mlx.info->texture[r], textureOffsetX, textureOffsetY);
		mlx_put_pixel(mlx.r_image, x->ray, y, color);
		y++;
	}
}

void rays_utils(t_mlx mlx, double angle, double start_angle, int r)
{
	t_point *a;
	t_point *b;

	angle = angle_corrector(start_angle + r * PLAYER_FOV / NUM_RAYS);
	a = calculate_horizontal_intersection(mlx, angle);
	b = calculate_vertical_intersection(mlx, angle);
	b->vertical = true;
	a->angle = angle;
	b->angle = angle;
	a->ray = r;
	b->ray = r;
	if (a->x > 0 && a->x < mlx.info->width * SIZE && a->y > 0 && a->y < mlx.info->height * SIZE && a->distance < b->distance)
		render3d(mlx, a);
	else if (b->x > 0 && b->x < mlx.info->width * SIZE && b->y > 0 && b->y < mlx.info->height * SIZE && a->distance >= b->distance)
		render3d(mlx, b);
	free(a);
	free(b);
}

void display_rays(t_mlx mlx)
{
	double start_angle;
	double angle;
	int r;

	start_angle = angle_corrector(mlx.info->player_angle - PLAYER_FOV / 2.0f);
	angle = start_angle;
	r = 0;
	while (r < NUM_RAYS)
	{
		rays_utils(mlx, angle, start_angle, r);
		r++;
	}
	// mlx_image_to_window(mlx.mlx, mlx.r_image, 0, 0);
}

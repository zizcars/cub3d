/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:40:41 by achakkaf          #+#    #+#             */
/*   Updated: 2024/10/27 13:35:10 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

// static bool	is_gape(char **map, int x, int y, int nx, int ny)
static bool	is_gape(char **map, t_point tp, int nx, int ny)
{
	int	x;
	int	y;

	x = tp.x / SIZE;
	y = tp.y / SIZE;
	if ((int)ft_strlen(map[ny]) > nx && \
		(map[ny][nx] == '1' || map[ny][nx] == '\0' || map[ny][nx] == SPACE))
		return (true);
	else if ((int)ft_strlen(map[y]) > nx && (int)ft_strlen(map[ny]) > x \
		&& map[ny][x] == '1' && map[y][nx] == '1')
		return (true);
	return (false);
}

void	find_horizontal_intersection(t_mlx mlx, double angle, t_point *a)
{
	t_point	p;
	t_point	tp;

	tp.x = a->x;
	tp.y = a->y;
	while (a->x > 0 && a->x < mlx.info->width * SIZE \
		&& a->y > 0 && a->y < mlx.info->height * SIZE)
	{
		if (is_gape(mlx.info->map, tp, a->x / SIZE, a->y / SIZE))
			break ;
		if (angle <= M_PI && angle >= 0)
			p.y = SIZE;
		else
			p.y = -SIZE;
		p.x = p.y / tan(angle);
		tp.x = a->x;
		tp.y = a->y;
		a->x += p.x;
		a->y += p.y;
	}
}

t_point	*calculate_horizontal_intersection(t_mlx mlx, double angle)
{
	t_point	*a;

	a = ft_calloc(1, sizeof(t_point));
	if (a == NULL)
		ft_error("malloc faild");
	if (angle <= M_PI && angle >= 0)
		a->y = floor(mlx.info->player_y / SIZE) * SIZE + SIZE;
	else
		a->y = floor(mlx.info->player_y / SIZE) * SIZE - 0.00001;
	a->x = (a->y - mlx.info->player_y) / tan(angle) + mlx.info->player_x;
	find_horizontal_intersection(mlx, angle, a);
	if (a->x > 0 && a->x < mlx.info->width * SIZE \
		&& a->y > 0 && a->y < mlx.info->height * SIZE)
		a->distance = sqrt(pow(mlx.info->player_x - a->x, 2) \
			+ pow(mlx.info->player_y - a->y, 2));
	else
		a->distance = 2147483647;
	return (a);
}

void	find_vertical_intersection(t_mlx mlx, const double angle, t_point *a)
{
	t_point	p;
	t_point	tp;

	tp.x = a->x;
	tp.y = a->y;
	while (a->x > 0 && a->x < mlx.info->width * SIZE \
		&& a->y > 0 && a->y < mlx.info->height * SIZE)
	{
		if (is_gape(mlx.info->map, tp, a->x / SIZE, a->y / SIZE))
			break ;
		if (angle <= (3 * M_PI) / 2 && angle >= M_PI / 2)
			p.x = -SIZE;
		else
			p.x = SIZE;
		p.y = p.x * tan(angle);
		tp.x = a->x;
		tp.y = a->y;
		a->x += p.x;
		a->y += p.y;
	}
}

t_point	*calculate_vertical_intersection(t_mlx mlx, const double angle)
{
	t_point	*a;

	a = ft_calloc(1, sizeof(t_point));
	if (a == NULL)
		ft_error("malloc faild");
	if (angle <= (3 * M_PI) / 2 && angle >= M_PI / 2)
		a->x = (mlx.info->player_x / SIZE) * SIZE - 0.00001;
	else
		a->x = (mlx.info->player_x / SIZE) * SIZE + SIZE;
	a->y = mlx.info->player_y + (a->x - mlx.info->player_x) * tan(angle);
	find_vertical_intersection(mlx, angle, a);
	if (a->x > 0 && a->x < mlx.info->width * SIZE \
		&& a->y > 0 && a->y < mlx.info->height * SIZE)
		a->distance = sqrt(pow(mlx.info->player_x - a->x, 2) + \
			pow(mlx.info->player_y - a->y, 2));
	else
		a->distance = 2147483647;
	return (a);
}

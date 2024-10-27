/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:03:48 by achakkaf          #+#    #+#             */
/*   Updated: 2024/10/27 13:25:56 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

static void	move_up(t_mlx *mlx, double *tmp_x, double *tmp_y)
{
	*tmp_x = round(mlx->info->player_x + cos(mlx->info->player_angle) * SPEED);
	*tmp_y = round(mlx->info->player_y + sin(mlx->info->player_angle) * SPEED);
	if (mlx->info->player_angle <= (3 * M_PI) / 2 && \
		mlx->info->player_angle >= M_PI / 2)
		mlx->info->check_x = -CHECK_N;
	else
		mlx->info->check_x = CHECK_N;
	if (mlx->info->player_angle <= M_PI && mlx->info->player_angle >= 0)
		mlx->info->check_y = CHECK_N;
	else
		mlx->info->check_y = -CHECK_N;
}

static void	move_down(t_mlx *mlx, double *tmp_x, double *tmp_y)
{
	*tmp_x = round(mlx->info->player_x - cos(mlx->info->player_angle) * SPEED);
	*tmp_y = round(mlx->info->player_y - sin(mlx->info->player_angle) * SPEED);
	if (mlx->info->player_angle <= (3 * M_PI) / 2 && \
		mlx->info->player_angle >= M_PI / 2)
		mlx->info->check_x = CHECK_N;
	else
		mlx->info->check_x = -CHECK_N;
	if (mlx->info->player_angle <= M_PI && mlx->info->player_angle >= 0)
		mlx->info->check_y = -CHECK_N;
	else
		mlx->info->check_y = CHECK_N;
}

static void	move_right(t_mlx *mlx, double *tmp_x, double *tmp_y)
{
	*tmp_x = round(mlx->info->player_x + cos(\
		angle_corrector(mlx->info->player_angle + M_PI_2)) * SPEED);
	*tmp_y = round(mlx->info->player_y + sin(\
		angle_corrector(mlx->info->player_angle + M_PI_2)) * SPEED);
	if (mlx->info->player_angle <= (3 * M_PI) / 2 && \
		mlx->info->player_angle >= M_PI / 2)
		mlx->info->check_y = -CHECK_N;
	else
		mlx->info->check_y = CHECK_N;
	if (mlx->info->player_angle <= M_PI && mlx->info->player_angle >= 0)
		mlx->info->check_x = -CHECK_N;
	else
		mlx->info->check_x = CHECK_N;
}

static void	move_left(t_mlx *mlx, double *tmp_x, double *tmp_y)
{
	*tmp_x = round(mlx->info->player_x + cos(\
		angle_corrector(mlx->info->player_angle - M_PI_2)) * SPEED);
	*tmp_y = round(mlx->info->player_y + sin(\
		angle_corrector(mlx->info->player_angle - M_PI_2)) * SPEED);
	if (mlx->info->player_angle <= (3 * M_PI) / 2 && \
		mlx->info->player_angle >= M_PI / 2)
		mlx->info->check_y = CHECK_N;
	else
		mlx->info->check_y = -CHECK_N;
	if (mlx->info->player_angle <= M_PI && mlx->info->player_angle >= 0)
		mlx->info->check_x = CHECK_N;
	else
		mlx->info->check_x = -CHECK_N;
}

void	move(t_mlx *mlx, E_DIRECTION d)
{
	double	tmp_y;
	double	tmp_x;

	tmp_y = 0;
	tmp_x = 0;
	if (d == UP)
		move_up(mlx, &tmp_x, &tmp_y);
	else if (d == DOWN)
		move_down(mlx, &tmp_x, &tmp_y);
	else if (d == RIGHT)
		move_right(mlx, &tmp_x, &tmp_y);
	else if (d == LEFT)
		move_left(mlx, &tmp_x, &tmp_y);
	if (move_check(*mlx, (tmp_x + mlx->info->check_x) / SIZE, \
		(tmp_y + mlx->info->check_y) / SIZE))
	{
		mlx->info->player_y = tmp_y;
		mlx->info->player_x = tmp_x;
	}
}

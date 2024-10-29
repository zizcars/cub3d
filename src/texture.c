/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:29:20 by abounab           #+#    #+#             */
/*   Updated: 2024/10/29 16:29:44 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

// have to free it later after use
int	load_all_textures(t_info **info)
{
	(*info)->texture[0] = mlx_load_png((*info)->north_path);
	if (!(*info)->texture[0])
		return (0);
	(*info)->texture[1] = mlx_load_png((*info)->south_path);
	if (!(*info)->texture[1])
		return (0);
	(*info)->texture[2] = mlx_load_png((*info)->east_path);
	if (!(*info)->texture[2])
		return (0);
	(*info)->texture[3] = mlx_load_png((*info)->west_path);
	if (!(*info)->texture[3])
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:29:20 by abounab           #+#    #+#             */
/*   Updated: 2024/10/06 20:07:05 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/types.h"
#include "../includes/parsing.h"

static uint32_t	*load_texture(char *texture_file)
{
	mlx_texture_t *texture;
	uint32_t *texture_arr = malloc (BOX * BOX * sizeof(uint32_t));
	float scale[2];
	if (!texture_file || texture_arr)
		return NULL;
	texture = mlx_load_png(texture_file);
	if (!texture)
		return NULL;
		// height scale
	scale[0] = (float) texture->height / BOX;
		// width scale
	scale[1] = (float) texture->width / BOX;
	// have to scale the texture
	for (int i = 0; i < BOX; i++)
	{
		for (int j = 0; j < BOX; j++)
		{
			int y = (int)(i * scale[0]);
			int x = (int)(j * scale[1]);
			texture_arr[i * BOX + j] = ((uint32_t*)texture->pixels)[y * texture->width + x];
		}
	}
	return texture_arr;
}

int load_all_textures(t_info **info)
{
	// have to free it later after use
	(*info)->texture[0] = load_texture((*info)->north_path);
	if (!(*info)->texture[0])
		return 0;
	(*info)->texture[1] = load_texture((*info)->south_path);
	if (!(*info)->texture[1])
		return 0;
	(*info)->texture[2] = load_texture((*info)->east_path);
	if (!(*info)->texture[2])
		return 0;
	(*info)->texture[3] = load_texture((*info)->west_path);
	if (!(*info)->texture[3])
		return 0;
	return 1;
}
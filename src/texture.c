/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:29:20 by abounab           #+#    #+#             */
/*   Updated: 2024/10/08 22:49:06 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/types.h"
#include "../includes/parsing.h"

static t_texture	*load_texture(char *texture_file)
{
	mlx_texture_t *texture;
	t_texture *ptr = ft_calloc(1, sizeof(t_texture));
	ptr->pixels = ft_calloc (BOX * BOX, sizeof(uint32_t));
	float scale[2];
	if (!texture_file || !ptr->pixels)
		return NULL;
	texture = mlx_load_png("maps/texture/bricks.png");
	// mlx_texture_to_image(&mlx, texture);
	if (!texture)
		return NULL;
	ptr->height = texture->height;
	ptr->width = texture->width;
		// height scale : y
	scale[0] = (float) texture->height / BOX;
		// width scale : x
	scale[1] = (float) texture->width / BOX;
	// have to scale the texture
	for (int i = 0; i < BOX; i++)
	{
		int y = (int)(i * scale[0]);
		for (int j = 0; j < BOX; j++)
		{
			int x = (int)(j * scale[1]);
			ptr->pixels[i * BOX + j] = ((uint32_t*)texture->pixels)[y * texture->width + x];
			// for (int k = 0; k < BOX; k++)
			// 	printf("%d\t",ptr->pixels[k]);
			// printf("\n");
		}
	}
	free(texture);
	return ptr;
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
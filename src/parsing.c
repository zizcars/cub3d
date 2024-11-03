/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:11:05 by achakkaf          #+#    #+#             */
/*   Updated: 2024/11/03 14:35:08 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

void	ft_error(char *error_ms)
{
	write(STDERR_FILENO, error_ms, ft_strlen(error_ms));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

static void	fill_info(char *tmp, t_info *info)
{
	if (tmp[0] == 'N' && tmp[1] == 'O' && (tmp[2] == SPACE || tmp[2] == TAB))
		store_path(tmp, &info->north_path);
	else if (tmp[0] == 'S' && tmp[1] == 'O' && 
		(tmp[2] == SPACE || tmp[2] == TAB))
		store_path(tmp, &info->south_path);
	else if (tmp[0] == 'W' && tmp[1] == 'E' && 
		(tmp[2] == SPACE || tmp[2] == TAB))
		store_path(tmp, &info->west_path);
	else if (tmp[0] == 'E' && tmp[1] == 'A' && 
		(tmp[2] == SPACE || tmp[2] == TAB))
		store_path(tmp, &info->east_path);
	else if (tmp[0] == 'C' && (tmp[1] == SPACE || tmp[1] == TAB))
		store_color(tmp, &info->c_color);
	else if (tmp[0] == 'F' && (tmp[1] == SPACE || tmp[1] == TAB))
		store_color(tmp, &info->f_color);
	else if (!tmp[0])
		return ;
	else
		ft_error("Invalid information");
}

void	check_info(t_info *info)
{
	if (info->east_path == NULL || info->north_path == NULL 
		|| info->south_path == NULL || info->west_path == NULL)
		ft_error("A texter path is missing");
	if (info->c_color == NULL || info->f_color == NULL)
		ft_error("Color is missing");
}

t_info	*read_info(int fd)
{
	char	*line;
	char	*tmp;
	t_info	*info;

	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		return (NULL);
	line = get_next_line(fd);
	tmp = ft_strtrim(line, " 	\n");
	while (tmp && tmp[0] != '1')
	{
		free(line);
		fill_info(tmp, info);
		free(tmp);
		line = get_next_line(fd);
		tmp = ft_strtrim(line, " 	\n");
	}
	free(tmp);
	check_info(info);
	take_map(info, line, fd);
	if (!load_all_textures(&info))
		return (free_info(info), NULL);
	return (info);
}

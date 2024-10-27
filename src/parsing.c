/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:11:05 by achakkaf          #+#    #+#             */
/*   Updated: 2024/10/27 13:02:57 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

// print Error massege in stderr
void	ft_error(char *error_ms)
{
	write(STDERR_FILENO, error_ms, ft_strlen(error_ms));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

static bool	check_file_char(char c)
{
	char	*chars;

	chars = "NSWECF";
	while (*chars)
	{
		if (*chars == c)
			return (false);
		chars++;
	}
	return (true);
}

static void	fill_info(char *tmp, t_info *info)
{
	store_path(tmp, 'N', 'O', &info->north_path);
	store_path(tmp, 'S', 'O', &info->south_path);
	store_path(tmp, 'W', 'E', &info->west_path);
	store_path(tmp, 'E', 'A', &info->east_path);
	store_color(tmp, 'C', &info->c_color);
	store_color(tmp, 'F', &info->f_color);
	if (check_file_char(tmp[0]) && tmp[0] != '\0')
		ft_error("Invalid information");
}

void	check_info(t_info *info)
{
	if (info->east_path == NULL || info->north_path == NULL \
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
	{
		free_info(info);
		return (NULL);
	}
	return (info);
}

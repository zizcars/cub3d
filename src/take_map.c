/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:55:02 by achakkaf          #+#    #+#             */
/*   Updated: 2024/10/27 13:35:35 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

static void	check_after_map(t_info *info, char *line, int fd)
{
	int	i;

	i = 0;
	if (info->map == NULL)
		ft_error("No map");
	line = get_next_line(fd);
	while (line)
	{
		while (line[i] && line[i] != '\n' && \
			(line[i] == SPACE || line[i] == TAB))
			i++;
		if (line[i] != '\n' && line[i] != '\0')
			ft_error("More content after the map");
		free(line);
		line = get_next_line(fd);
	}
	check_map(info);
}

void	take_map(t_info *info, char *line, int fd)
{
	int		len;
	char	*tmp;

	info->width = 0;
	info->height = 0;
	while (line && line[0] != '\n')
	{
		len = ft_strlen(line);
		tmp = line;
		line = ft_substr(line, 0, len - 1);
		free(tmp);
		if (line && line[0])
		{
			info->map = append_array(info->map, line);
			info->height++;
		}
		if (info->width < len)
			info->width = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	check_after_map(info, line, fd);
}

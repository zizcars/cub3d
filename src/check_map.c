/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:48:01 by achakkaf          #+#    #+#             */
/*   Updated: 2024/10/27 15:04:26 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

bool	invalid(char c)
{
	return (c == SPACE || c == '\0');
}

static void	check_first_line(char **map)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] == SPACE)
		{
			if ((int)ft_strlen(map[1]) >= i && (map[1][i] != SPACE && \
				map[1][i] != '1' && map[1][i] != '\0'))
				ft_error("The map not srounded by walls");
		}
		else if (map[0][i] != '1')
			ft_error("The map not srounded by walls");
		i++;
	}
}

static void	check_last_line(char *last_line)
{
	int	i;

	i = 0;
	while (last_line[i])
	{
		if (last_line[i] != '1' && last_line[i] != SPACE)
			ft_error("Map not srounded by walls");
		i++;
	}
}

static void	check_others(char **map, int i, int j)
{
	if (check_char(map[i][j]) == false)
		ft_error("invalid char");
	if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
	{
		if (((int)ft_strlen(map[i + 1]) >= j && invalid(map[i + 1][j])) || (int)ft_strlen(map[i + 1]) < j)
			ft_error("Map not srounded by walls");
		else if (((int)ft_strlen(map[i - 1]) > j && invalid(map[i - 1][j])) || (int)ft_strlen(map[i - 1]) < j)
			ft_error("Map not srounded by walls");
		else if (invalid(map[i][j + 1]))
			ft_error("Map not srounded by walls");
	}
}

void	check_map(t_info *info)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	check_first_line(info->map);
	i = 1;
	if (info->map[i] == NULL)
		ft_error("Invalid map");
	while (info->map[i + 1])
	{
		j = 0;
		while (info->map[i][j])
		{
			check_others(info->map, i, j);
			if (info->map[i][j] != '0' && info->map[i][j] != '1' && info->map[i][j] != SPACE)
				set_player_info(info, j, i, &count);
			j++;
		}
		i++;
	}
	if (count != 1)
		ft_error("Problem in the Player numeber in the map");
	check_last_line(info->map[i]);
}

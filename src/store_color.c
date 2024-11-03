/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:48:14 by achakkaf          #+#    #+#             */
/*   Updated: 2024/11/03 16:41:15 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

static void	check_color_number(char **color_split, int i, int *count)
{
	int	j;

	j = 0;
	while (color_split[i] && color_split[i][j])
	{
		if (color_split[i][j] == '-' || color_split[i][j] == '+')
			(*count)++;
		else if (ft_isdigit(color_split[i][j]) == -1)
			ft_error("The color must be a number");
		if (*count > 1)
			ft_error("Invalid color number");
		j++;
	}
}

static void	take_color(char **color_split, int **color, char *tmp)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < 3)
	{
		tmp = color_split[i];
		color_split[i] = ft_strtrim(color_split[i], "	 ");
		free(tmp);
		check_color_number(color_split, i, &count);
		if (color_split[i] && color_split[i][0])
			(*color)[i] = ft_atoi(color_split[i]);
		else
			ft_error("Invalid color number");
		if ((*color)[i] < 0 || (*color)[i] > 255)
			ft_error("The color number must be in this range [0, 255]");
		count = 0;
		i++;
	}
}

static void	check_comas(char *tmp)
{
	int		i;
	int		count_coma;

	i = 0;
	count_coma = 0;
	while(tmp[i])
	{
		if (tmp[i] == ',')
			count_coma++;
		else if (ft_isdigit(tmp[i]) == 0)
			count_coma = 0;
		if (count_coma > 1)
			ft_error("Invalid color number");
		i++;
	}
	if (count_coma != 0)
		ft_error("Invalid color number");
}

static int	*take_color_init(char *s_color)
{
	int		*color;
	char	*tmp;
	char	**color_split;


	color = ft_calloc(3, sizeof(int));
	if (color == NULL)
		ft_error("Malloc Flailed");
	tmp = ft_substr(s_color, 1, ft_strlen(s_color));
	check_comas(tmp);
	color_split = ft_split(tmp, ',');
	free(tmp);
	if (array_length(color_split) > 3)
		ft_error("Invalid color number");
	take_color(color_split, &color, tmp);
	free_array(&color_split);
	return (color);
}

void	store_color(char *tmp, int **color_box)
{
	free(*color_box);
	*color_box = take_color_init(tmp);
}

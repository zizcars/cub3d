/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:56:21 by achakkaf          #+#    #+#             */
/*   Updated: 2024/11/03 20:27:10 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

static char	*take_diraction_path(char *trim_line)
{
	int	start;
	int	i;

	i = 2;
	while (trim_line[i] == SPACE || trim_line[i] == TAB)
		i++;
	start = i;
	while (trim_line[i] != SPACE && trim_line[i] != TAB && trim_line[i] != '\0')
		i++;
	return (ft_substr(trim_line, start, i));
}

void	store_path(char *tmp, char **path_box)
{
	free(*path_box);
	*path_box = take_diraction_path(tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:22:12 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/10/27 14:47:05 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*get_one_line(char *s)
{
	char	*line;
	int		i;
	int		len;

	i = 0; 
	len = find_nl(s);
	if (len > -1)
		len++;
	else
	{
		len = ft_strlen(s);
		if (len == 0)
			return (NULL);
	}
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	find_nl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*rm_line(char *s)
{
	char	*new_s;
	int		start;
	int		i;

	i = 0;
	start = 0;
	start = find_nl(s);
	if (start == -1)
		return (NULL);
	start++;
	new_s = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	while (s[start])
		new_s[i++] = s[start++];
	new_s[i] = '\0';
	return (new_s);
}

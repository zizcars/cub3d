/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:22:10 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/10/27 14:46:56 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static char	*ft_free(char **s)
{
	free(*s);
	*s = NULL;
	return (NULL);
}

static char	*m_bytes(char **str, char **buffer, int bytes, char *line)
{
	char	*tmp;

	if (bytes == -1)
	{
		ft_free(str);
		return (ft_free(buffer));
	}
	else if (bytes == 0)
	{
		tmp = *str;
		line = get_one_line(*str);
		if (line == NULL)
		{
			ft_free(str);
			return (ft_free(buffer));
		}
		*str = rm_line(*str);
		ft_free(&tmp);
		ft_free(buffer);
		return (line);
	}
	return (line);
}

static char	*re_line(char **buffer, char **str, int bytes, char *line)
{
	char	*tmp;

	(*buffer)[bytes] = '\0';
	tmp = *str;
	*str = ft_strjoin(*str, *buffer);
	ft_free(&tmp);
	if (*str == NULL)
		return (ft_free(buffer));
	if (find_nl(*str) > -1)
	{
		line = get_one_line(*str);
		if (line == NULL)
		{
			ft_free(str);
			return (ft_free(buffer));
		}
		tmp = *str;
		*str = rm_line(*str);
		ft_free(&tmp);
		ft_free(buffer);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;
	char		*line;
	int			bytes;

	if (BUFFER_SIZE < 1)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (ft_free(&str));
	bytes = 1;
	line = NULL;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		line = re_line(&buffer, &str, bytes, line);
		if (find_nl(line) > -1)
			return (line);
	}
	line = m_bytes(&str, &buffer, bytes, line);
	ft_free(&buffer);
	return (line);
}

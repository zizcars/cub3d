/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:22:10 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/07/22 16:50:04 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char **s)
{
	free(*s);
	*s = NULL;
	return (NULL);
}

// static char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*store;
// 	int		i;

// 	i = 0;
// 	if (!s1 && !s2)
// 		return (NULL);
// 	else if (!s1)
// 		return (ft_strdup(s2));
// 	else if (!s2)
// 		return (ft_strdup(s1));
// 	store = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
// 	if (!store)
// 		return (NULL);
// 	while (*s1)
// 		store[i++] = *(s1++);
// 	while (*s2)
// 		store[i++] = *(s2++);
// 	store[i] = '\0';
// 	return (store);
// }

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
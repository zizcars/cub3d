/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:22:05 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/10/17 15:50:24 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "../libs/libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
char	*get_one_line(char *s);
char	*rm_line(char *s);
int		find_nl(char *s);

#endif
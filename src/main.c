/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:13:37 by achakkaf          #+#    #+#             */
/*   Updated: 2024/11/03 17:55:59 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utiles.h"

int	main(int ac, char **av)
{
	int		fd;
	t_mlx	mlx;

	if (ac == 2)
	{
		if (check_filename(av[1]) == false)
			ft_error("Invalid filetype: *.cub");
		fd = open(av[1], O_RDWR);
		if (fd < 0)
			ft_error("no file");
		mlx.info = read_info(fd);
		if (!mlx.info)
			return (ft_error("error on elements"), 1);
		close(fd);
		display_window(&mlx);
	}
	else
		ft_error("./cub3D /path/to/a/map.ber\nExemple:\n./cub3D maps/map.ber");
}

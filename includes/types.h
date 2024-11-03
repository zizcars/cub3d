/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:14:32 by achakkaf          #+#    #+#             */
/*   Updated: 2024/11/03 09:47:58 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <fcntl.h>
# include <math.h>
# include "../libs/libft/libft.h"
# include "get_next_line.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define WIDTH 1280
# define HEIGHT 720
# define BOX 20
# define NUM_RAYS 1280

# define FACTOR 0.4
# define ROTATION_ANGLE 5
# define SPACE 32
# define TAB 9
# define SIZE 20
# define SPEED 6
# define PLAYER_FOV 1.047198

# define FRAME_Y 160
# define FRAME_X 284
# define CHECK_N 2

# define MOUSE_R 2

typedef enum S_direction{
	UP = 1,
	DOWN = 2,
	RIGHT = 3,
	LEFT = 4,
}	t_direction;

typedef struct s_texture
{
	uint32_t	*pixels;
	uint32_t	height;
	uint32_t	width;
}	t_texture;

typedef struct s_info
{
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	mlx_texture_t	*texture[4];
	int				*f_color;
	int				*c_color;
	char			**map;
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	double			player_angle;
	int				check_x;
	int				check_y;
}	t_info;

typedef struct s_point
{
	double	x;
	double	y;
	double	distance;
	bool	vertical;
	double	angle;
	int		ray;
}	t_point;

typedef struct s_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*r_image;
	t_info		*info;
}	t_mlx;

typedef struct s_render
{
	int		texture_off_set_x;
	int		texture_off_set_y;
	double	start_pix;
	double	end_pix;
	double	wall_h;
	int		r;
}	t_render;

#endif

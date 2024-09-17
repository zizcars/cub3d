#include "../includes/parsing.h"

/// @brief check if file name end with .cub
bool check_filename(char *file_name)
{
	char *tmp;

	if (file_name == NULL)
		return (false);
	tmp = ft_strrchr(file_name, '.');
	if (tmp == NULL)
		return (false);
	if (ft_strcmp(tmp, ".cub") == 0)
		return (true);
	return (false);
}

// check a char is valid
bool check_char(char c)
{
	const char *valid_char;

	valid_char = "01NSEW ";
	while (*valid_char && c != '\0')
	{
		if (c == *valid_char)
			return (true);
		valid_char++;
	}
	return (false);
}

/// @brief check if the values of color are correct
/// @param color like 32,255,255
/// @return true if valid else false
bool check_color(int *color)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
			return true;
		i++;
	}
	return (false);
}

void check_map(t_info *info)
{
	int i;
	int j;
	int len;
	int count;

	j = 0;
	count = 0;
	while (info->arr_map[0][j] && info->arr_map[0][j] == '1')
		j++;
	if (info->arr_map[0][j] != '\0')
		ft_error("first line not 1");
	i = 1;
	while (info->arr_map[i + 1])
	{
		len = j;
		j = 0;
		while (info->arr_map[i][j])
		{
			if (check_char(info->arr_map[i][j]) == false)
				ft_error("invalid char");
			if (info->arr_map[i][j] != '0' && info->arr_map[i][j] != '1')
				count++;
			if (info->arr_map[i][j] != '1' && (len <= j || ft_strlen(info->arr_map[i + 1]) <= j))
				ft_error("the map not srounded by walls");
			if (info->arr_map[i][j] != '0' && info->arr_map[i][j] != '1')
			{
				info->player_x = j * SIZE;
				info->player_y = i * SIZE;
				if (info->arr_map[i][j] == 'N')
					info->player_angle = 270;
				else if (info->arr_map[i][j] == 'E')
					info->player_angle = 0;
				else if (info->arr_map[i][j] == 'S')
					info->player_angle = 90;
				else 
					info->player_angle = 180;
			}
			j++;
		}
		if (info->arr_map[i][0] != '1' || info->arr_map[i][j - 1] != '1')
			ft_error("first or last char in line not 1");
		i++;
	}
	j = 0;
	while (info->arr_map[i][j] && info->arr_map[i][j] == '1')
		j++;
	if (info->arr_map[i][j] != '\0')
		ft_error("last line not 1");
	if (count != 1)
		ft_error("Problem in the Player numeber in the map");
}


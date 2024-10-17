#include "../includes/utiles.h"

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

int check_ones(char *line)
{
	int i;
	bool is_one;

	is_one = false;
	i = 0;
	while (line[i] && line[i] == SPACE)
		i++;
	while (line[i] && line[i] == '1')
	{
		is_one = true;
		i++;
	}
	while (line[i] && line[i] == SPACE)
		i++;
	if (line[i] != '\0' || is_one == false)
		exit(1);
	return (i);
}

void set_player_info(t_info *info, int x, int y)
{
	info->player_x = x * SIZE + SIZE / 2;
	info->player_y = y * SIZE + SIZE / 2;
	if (info->arr_map[y][x] == 'N')
		info->player_angle = (270 * M_PI) / 180.0f;
	else if (info->arr_map[y][x] == 'E')
		info->player_angle = 0;
	else if (info->arr_map[y][x] == 'S')
		info->player_angle = (90 * M_PI) / 180.0f;
	else
		info->player_angle = (180 * M_PI) / 180.0f;
}

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
	{
		// printf("line: %s => %c\n", line, line[i]);
		exit(1);
		// ft_error("The map not srounded by walls");
	}
	return i;
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

// void check_around(char **map, int x, int y, int height)
// {
// 	if (map[y][x] == '\0')
// 		return;
// 	if (map[y][x] == '1' && map[y + 1][x] == '\0')
// 		return;
// 	printf("(%d, %d) = |%c| -> y+1[%c] -> x+1[%c] \n", x, y, map[y][x], map[y + 1][x], map[y][x + 1]);
// 	if (map[y][x] == '0' && (map[y + 1][x] == SPACE || map[y + 1][x] == '\0'))
// 	{
// 		printf("error (%d, %d) = |%c|\n", x, y + 1, map[y][x + 1]);
// 		ft_error("Map not srounded by walls 1");
// 	}
// 	if (map[y][x] == '0' && (map[y][x + 1] == SPACE || map[y][x + 1] == '\0'))
// 	{
// 		printf("error (%d, %d) = |%c|\n", x + 1, y, map[y][x + 1]);
// 		ft_error("Map not srounded by walls 2");
// 	}
// 	check_around(map, x + 1, y, height);
// 	check_around(map, 0, y + 1, height);
// }

bool invalid(char c)
{
	return (c == SPACE || c == '\0');
}

bool is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void check_first_line(char **map)
{
	int j;

	j = 0;
	while (map[0][j])
	{
		if (map[0][j] == SPACE)
		{
			if ((int)ft_strlen(map[1]) >= j && (map[1][j] != SPACE && map[1][j] != '1' && map[1][j] != '\0')) // what if map has one line
				ft_error("The map not srounded by walls 0000");
		}
		else if (map[0][j] != '1')
			ft_error("The map not srounded by walls 0001");
		j++;
	}
}

static void check_last_line(char *last_line)
{
	int j;

	j = 0;
	while (last_line[j])
	{
		if (last_line[j] != '1' && last_line[j] != SPACE)
			ft_error("Map not srounded by walls 0005");
		j++;
	}
}

static void check_others(char **map, int i, int j)
{
	if (check_char(map[i][j]) == false)
		ft_error("invalid char");
	if (map[i][j] == '0' || is_player(map[i][j]))
	{
		if ((int)ft_strlen(map[i + 1]) >= j && invalid(map[i + 1][j]))
			ft_error("Map not srounded by walls 1");
		else if ((int)ft_strlen(map[i - 1]) > j && invalid(map[i - 1][j]))
			ft_error("Map not srounded by walls 2");
		else if (invalid(map[i][j + 1]))
			ft_error("Map not srounded by walls 3");
		else if (j > 0 && invalid(map[i][j - 1]))
			ft_error("Map not srounded by walls 4");
	}
}

void check_map(t_info *info)
{
	int i;
	int j;
	int count;

	count = 0;
	check_first_line(info->arr_map);
	i = 1;
	if (info->arr_map[i] == NULL)
		ft_error("Invalid map");
	while (info->arr_map[i + 1])
	{
		j = 0;
		while (info->arr_map[i][j])
		{
			check_others(info->arr_map, i, j);
			if (info->arr_map[i][j] != '0' && info->arr_map[i][j] != '1' && info->arr_map[i][j] != SPACE)
			{
				set_player_info(info, j, i);
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		ft_error("Problem in the Player numeber in the map");
	check_last_line(info->arr_map[i]);
}

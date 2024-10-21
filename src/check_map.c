
#include "../includes/utiles.h"

bool invalid(char c)
{
	return (c == SPACE || c == '\0');
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
				ft_error("The map not srounded by walls");
		}
		else if (map[0][j] != '1')
			ft_error("The map not srounded by walls");
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
			ft_error("Map not srounded by walls");
		j++;
	}
}

static void check_others(char **map, int i, int j)
{
	if (check_char(map[i][j]) == false)
		ft_error("invalid char");
	if (map[i][0] != '1')
		ft_error("Map not srounded by walls");
	if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
	{
		if ((int)ft_strlen(map[i + 1]) >= j && invalid(map[i + 1][j]))
			ft_error("Map not srounded by walls");
		else if ((int)ft_strlen(map[i - 1]) > j && invalid(map[i - 1][j]))
			ft_error("Map not srounded by walls");
		else if (invalid(map[i][j + 1]))
			ft_error("Map not srounded by walls");
		else if (j > 0 && invalid(map[i][j - 1]))
			ft_error("Map not srounded by walls");
	}
}

// void check_map(t_info *info)
// {
// 	int i;
// 	int j;
// 	int count;

// 	count = 0;
// 	check_first_line(info->arr_map);
// 	i = 1;
// 	if (info->arr_map[i] == NULL)
// 		ft_error("Invalid map");
// 	while (info->arr_map[i + 1])
// 	{
// 		j = 0;
// 		while (info->arr_map[i][j])
// 		{
// 			check_others(info->arr_map, i, j);
// 			if (info->arr_map[i][j] != '0' && info->arr_map[i][j] != '1' && info->arr_map[i][j] != SPACE)
// 			{
// 				set_player_info(info, j, i);
// 				count++;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (count != 1)
// 		ft_error("Problem in the Player numeber in the map");
// 	check_last_line(info->arr_map[i]);
// }

void check_map(char **map, int j, int i)
{
	if (j < 0 || i < 0 || map[i][j] == '\0')
		return;
	printf("(%d, %d) => [%c]\n", j, i, map[i][j]);
	if (map[i] && (int)ft_strlen(map[i]) < j)
		return;
	if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
	{
		if ((int)ft_strlen(map[i + 1]) >= j && invalid(map[i + 1][j]))
			ft_error("Map not srounded by walls");
		else if ((int)ft_strlen(map[i - 1]) > j && invalid(map[i - 1][j]))
			ft_error("Map not srounded by walls");
		else if (invalid(map[i][j + 1]))
			ft_error("Map not srounded by walls");
		else if (j > 0 && invalid(map[i][j - 1]))
			ft_error("Map not srounded by walls");
	}
	check_map(map, j - 1, i);
	check_map(map, j, i + 1);
	check_map(map, j + 1, i);
	check_map(map, j, i - 1);
}
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
bool is_check_char(char c)
{
	const char *valid_char;

	valid_char = "01NSEW";
	while (*valid_char && c != '\0')
	{
		if (c == *valid_char)
			return (true);
		valid_char++;
	}
	return (false);
}

/// @brief check the validation of a map
/// @param row the map
/// @return true if valid else false
// bool check_map(char *row)
// {
// 	int i;
// 	int player_count;

// 	player_count = 0;
// 	i = 0;
// 	while (row && row[i] != '\n')
// 	{
// 		if (row[i] != '1')
// 		{
// 			printf("false 1:|%c|\n", row[i]);
// 			return (false);
// 		}
// 		i++;
// 	}
// 	while (row && row[i])
// 	{
// 		if (row[i] == '\n' && row[i + 1] && row[i + 1] != '1')
// 		{
// 			printf("false 4\n");
// 			return (false);
// 		}
// 		if (row[i] == '\n')
// 		{
// 			if (row[i + 1] == '\n')
// 				return (false);
// 			i++;
// 			continue;
// 		}
// 		if (check_char(row[i]) == false)
// 		{
// 			printf("false 2\n");
// 			return (false);
// 		}
// 		if (row[i] != '1' && row[i + 1] && row[i + 1] == '\n')
// 		{
// 			printf("false 3\n");
// 			return (false);
// 		}
// 		if (row[i] == 'N' || row[i] == 'S' || row[i] == 'E' || row[i] == 'W')
// 			player_count++;
// 		if (player_count > 1)
// 			return (false);
// 		i++;
// 	}
// 	if (player_count != 1)
// 		return (false);
// 	i -= 2;
// 	while (i > 0 && row[i] != '\n')
// 	{
// 		if (row[i] != '1')
// 		{
// 			printf("false 5:|%c|\n", row[i]);
// 			return (false);
// 		}
// 		i--;
// 	}
// 	return (true);
// }

// calculate the length of an array
int array_length(char **array)
{
	int len;

	len = 0;
	while (array && array[len])
	{
		if (ft_strcmp(array[len], "\n") == 0) // I add array[len] == '\n' because in some cases the array is being like this [..., "\n", NULL];
			break;
		len++;
	}
	return (len);
}

void free_array(char ***array)
{
	int len;

	len = 0;
	while ((*array) && (*array)[len])
		free((*array)[len++]);
	free(*array);
}

// print Error massege in stderr
void ft_error(char *error_ms)
{
	write(STDERR_FILENO, error_ms, ft_strlen(error_ms));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

/// @brief check if the values of color are correct
/// @param color like 32,255,255
/// @return true if valid else false
bool check_color(char *color)
{
	int i;

	i = 0;
	while (color && color[i])
	{
		if (ft_isdigit(color[i]) && color[i] != ',')
			return (false);
		i++;
	}
	return (true);
}

// calculate the length of an array
int array_size(char **array)
{
	int size;

	size = 0;
	while (array && array[size])
		size++;
	return (size);
}

// append arg to end of old_array and free old_array
char **append_array(char **old_array, char *arg)
{
	int size;
	char **new_array;

	if (arg == NULL)
		return (old_array);
	size = array_size(old_array);
	new_array = malloc(sizeof(char *) * (size + 2));
	if (new_array == NULL)
		return (NULL);
	if (old_array == NULL)
	{
		new_array[0] = ft_strdup(arg);
		new_array[1] = NULL;
		return (new_array);
	}
	size = 0;
	while (old_array[size])
	{
		new_array[size] = ft_strdup(old_array[size]);
		size++;
	}
	free_array(&old_array);
	new_array[size++] = ft_strdup(arg);
	new_array[size] = NULL;
	return (new_array);
}

bool check_map(char **map)
{
	int i;
	int j;

	j = 0;
	while (map[0][j] && map[0][j] == '1')
		j++;
	if (map[0][j] != '\0')
		return false;
	i = 1;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_check_char(map[i][j]) == false)
			{
				ft_error("invalid char");
				return false;
			}
			j++;
		}
		if (map[i][0] != '1' || map[i][j - 1] != '1')
		{
			ft_error("first or last char in line not 1");
			return false;
		}
		i++;
	}
	j = 0 ;
	while (map[i - 1][j] && map[i - 1][j] == '1')
		j++;
	if (map[0][j] != '\0')
	{
		ft_error("last line not 1");
		return false;
	}
	return true;
}

// read the .cub file and return it as t_map_info
t_map_info *read_info(int fd)
{
	char *line;
	char **split_line;
	t_map_info *info;
	char *tmp;
	int ar_len;

	tmp = NULL;
	info = ft_calloc(1, sizeof(t_map_info));
	line = get_next_line(fd);
	split_line = ft_split(line, SPACE);
	// free(line);
	// printf("line: %s\n", line);
	while (split_line && split_line[0][0] != '1')
	{
		ar_len = array_length(split_line);
		if (ar_len == 2 && ft_strcmp(split_line[0], "NO") == 0)
		{
			free(info->north_path);
			info->north_path = ft_strdup(split_line[1]);
		}
		else if (ar_len == 2 && ft_strcmp(split_line[0], "SO") == 0)
		{
			free(info->south_path);
			info->south_path = ft_strdup(split_line[1]);
		}
		else if (ar_len == 2 && ft_strcmp(split_line[0], "WE") == 0)
		{
			free(info->west_path);
			info->west_path = ft_strdup(split_line[1]);
		}
		else if (ar_len == 2 && ft_strcmp(split_line[0], "EA") == 0)
		{
			free(info->east_path);
			info->east_path = ft_strdup(split_line[1]);
		}
		else if (ar_len == 2 && ft_strcmp(split_line[0], "F") == 0)
		{
			free(info->floor_color);
			if (check_color(split_line[1]) == false)
				ft_error("error");
			info->floor_color = ft_strdup(split_line[1]);
		}
		else if (ar_len == 2 && ft_strcmp(split_line[0], "C") == 0)
		{
			free(info->ceiling_color);
			if (check_color(split_line[1]) == false)
				ft_error("error");
			info->ceiling_color = ft_strdup(split_line[1]);
		}
		else if (split_line[0][0] == '\n')
		{
			line = get_next_line(fd);
			split_line = ft_split(line, SPACE);
			// free(line);
			continue;
		}
		else
			ft_error("error1");
		line = get_next_line(fd);
		split_line = ft_split(line, SPACE);
		// free(line);
	}
	while (line)
	{
		tmp = line;
		line = ft_strtrim(line, " \n");
		free(tmp);
		if (line && line[0])
			info->arr_map = append_array(info->arr_map, line);
		line = get_next_line(fd);
	}
	if (info->arr_map == NULL)
		ft_error("no map");
	else
		check_map(info->arr_map);
	return (info);
}

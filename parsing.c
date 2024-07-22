#include "parsing.h"

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

bool check_char(char c)
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

bool chack_map(char *row)
{
	int i;

	i = 0;
	while(row && row[i] && row[i] != '\n')
	{
		if (row[i] != '1')
			return (false);
		i++;
	}
	while (row && row[i])
	{
		if (check_char(row[i]) == false)
			return (false);
		if (row[i] != '1' && row[i + 1] && row[i + 1] == '\n')
			return (false);
		if (row[i] == '\n' && row[i + 1] && row[i + 1] != '1')
			return (false);
		if ()

	}
	
}
int array_lenght(char **array)
{
	int len;

	len = 0;
	while (array && array[len])
		len++;
	return (len);
}

void free_array(char ***array)
{
	int len;

	while ((*array) && (*array)[len])
		free((*array)[len++]);
	free(*array);
}

void ft_error()
{
	write(STDERR_FILENO, "Error\n", 7);
	exit(1);
}
t_map_info *read_info(int fd)
{
	char *line;
	char **split_line;
	t_map_info *info;
	char *tmp;
	tmp = NULL;
	// bool is_no;
	// bool is_so;
	// bool is_we;
	// bool is_ea;

	// is_no = false;
	// is_so = false;
	// is_we = false;
	// is_ea = false;
	info = ft_calloc(1, sizeof(t_map_info));
	line = get_next_line(fd);
	split_line = ft_split(line, SPACE);
	// free(line);
	while (split_line && split_line[0][0] != '1')
	{
		// printf("|%s|\n", split_line[0]);
		if (ft_strcmp(split_line[0], "NO") == 0)
		{
			free(info->north_path);
			info->north_path = ft_strdup(split_line[1]);
		}
		else if (ft_strcmp(split_line[0], "SO") == 0)
		{
			free(info->south_path);
			info->south_path = ft_strdup(split_line[1]);
		}
		else if (ft_strcmp(split_line[0], "WE") == 0)
		{
			free(info->west_path);
			info->west_path = ft_strdup(split_line[1]);
		}
		else if (ft_strcmp(split_line[0], "EA") == 0)
		{
			free(info->east_path);
			info->east_path = ft_strdup(split_line[1]);
		}
		else if (ft_strcmp(split_line[0], "F") == 0)
		{
			free(info->floor_color);
			info->floor_color = ft_strdup(split_line[1]);
		}
		else if (ft_strcmp(split_line[0], "C") == 0)
		{
			free(info->ceiling_color);
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
			ft_error();
		line = get_next_line(fd);
		split_line = ft_split(line, SPACE);
		// free(line);
	}
	while (line)
	{
		tmp = info->map;
		info->map = ft_strjoin(info->map, line);
		free(tmp);
		line = get_next_line(fd);
	}
	
	return (info);
}

#include "../includes/parsing.h"

// print Error massege in stderr
void ft_error(char *error_ms)
{
	write(STDERR_FILENO, error_ms, ft_strlen(error_ms));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

void take_map(t_info *info, char *line, int fd)
{
	int len;
	char *tmp;

	info->width = 0;
	info->height = 0;
	while (line)
	{
		tmp = line;
		line = ft_strtrim(line, " \n");
		free(tmp);
		if (line && line[0])
		{
			info->arr_map = append_array(info->arr_map, line);
			info->height++;
		}
		len = ft_strlen(line);
		if (info->width < len)
			info->width = len;
		line = get_next_line(fd);
	}
	if (info->arr_map == NULL)
		ft_error("no map");
	check_map(info);
}

int *take_color(char *s_color)
{
	char **tmp;
	int *color;
	int i = 0;

	color = malloc(sizeof(int) * 3);
	if (color == NULL)
		return NULL;
	tmp = ft_split(s_color, ',');
	if (array_length(tmp) != 3)
		ft_error("invalid color value");
	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(tmp[i]);
		i++;
	}
	free_array(&tmp);
	if (check_color(color))
		ft_error("invalid color");
	return (color);
}

// read the .cub file and return it as t_info
t_info *read_info(int fd)
{
	char *line;
	char **split_line;
	t_info *info;
	int ar_len;
	int i = 0;

	info = ft_calloc(1, sizeof(t_info));
	line = get_next_line(fd);
	split_line = ft_split(line, SPACE);
	while (split_line && split_line[0][0] != '1')
	{
		ar_len = array_length(split_line);
		if (ar_len == 2 && ft_strcmp(split_line[0], "NO") == 0)
			info->north_path = ft_strdup(split_line[1]);
		else if (ar_len == 2 && ft_strcmp(split_line[0], "SO") == 0)
			info->south_path = ft_strdup(split_line[1]);
		else if (ar_len == 2 && ft_strcmp(split_line[0], "WE") == 0)
			info->west_path = ft_strdup(split_line[1]);
		else if (ar_len == 2 && ft_strcmp(split_line[0], "EA") == 0)
			info->east_path = ft_strdup(split_line[1]);
		else if (ar_len == 2 && ft_strcmp(split_line[0], "F") == 0) // do I have to handle this case F 0,   255, 255
			info->f_color = take_color(split_line[1]);
		else if (ar_len == 2 && ft_strcmp(split_line[0], "C") == 0)
			info->c_color = take_color(split_line[1]);
		else if (split_line[0][0] == '\n')
		{
			line = get_next_line(fd);
			split_line = ft_split(line, SPACE);
			continue;
		}
		else
			ft_error("error1");
		line = get_next_line(fd);
		split_line = ft_split(line, SPACE);
	}
	take_map(info, line, fd);
	return (info);
}

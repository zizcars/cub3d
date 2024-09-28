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
	// int i;
	info->width = 0;
	info->height = 0;
	while (line && line[0] != '\n') // I add line[0] != '\n' empty lines in the map are not valid
	{
		len = ft_strlen(line);
		// i = len - 2;
		// while (i > 0 && (line[i] == SPACE || line[i] == TAB)) // line[i] == '\n'
		// 	i--;
		tmp = line;
		line = ft_substr(line, 0, len - 1);
		free(tmp);
		if (line && line[0])
		{
			info->arr_map = append_array(info->arr_map, line);
			info->height++;
		}
		if (info->width < len)
			info->width = len;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (info->arr_map == NULL)
		ft_error("No map");
	line = get_next_line(fd);
	int i = 0;
	while (line)
	{
		while(line[i] && line[i] != '\n' && (line[i] == SPACE || line[i] == TAB))
			i++;
		if (line[i] != '\n' && line[i] != '\0')
			ft_error("More content after the map");
		free(line);
		line = get_next_line(fd);
	}
	check_map(info);
}

int *take_color(char *s_color)
{
	int *color;
	int i;
	char *tmp;
	char **color_split;
	int count;
	int j;

	count = 0;
	i = 0;
	color = ft_calloc(3, sizeof(int));
	if (color == NULL)
		ft_error("Malloc flied");
	tmp = ft_substr(s_color, 1, ft_strlen(s_color));
	color_split = ft_split(tmp, ',');
	free(tmp);
	if (array_length(color_split) > 3)
		ft_error("Invalid color number");
	while (i < 3)
	{
		j = 0;
		tmp = color_split[i];
		color_split[i] = ft_strtrim(color_split[i], "	 ");
		free(tmp);
		while (color_split[i] && color_split[i][j])
		{
			if (color_split[i][j] == '-' || color_split[i][j] == '+')
				count++;
			else if (ft_isdigit(color_split[i][j]) == -1)
				ft_error("The color must be a number");
			if (count > 1)
				ft_error("Invalid color number");
			j++;
		}
		if (color_split[i] && color_split[i][0])
			color[i] = ft_atoi(color_split[i]);
		else
			ft_error("Invalid color number");
		if (color[i] < 0 || color[i] > 255)
			ft_error("The color number must be in this range [0, 255]");
		count = 0;
		i++;
	}
	free_array(&color_split);
	return color;
}

char *take_diraction_path(char *trim_line)
{
	int start;
	int i;

	i = 2;
	while (trim_line[i] == SPACE || trim_line[i] == TAB)
		i++;
	start = i;
	while (trim_line[i] != SPACE && trim_line[i] != TAB && trim_line[i] != '\0')
		i++;
	if (trim_line[i] == SPACE || trim_line[i] == TAB)
		ft_error("Invalid information");
	else
		return ft_substr(trim_line, start, i);
	return NULL;
}

// read the .cub file and return it as t_info
t_info *read_info(int fd)
{
	char *line;
	char *tmp;
	char **split_line;
	t_info *info;
	int ar_len;
	int i = 0;

	info = ft_calloc(1, sizeof(t_info));
	info->player_fov = (60 * M_PI) / 180.0f;
	line = get_next_line(fd);
	tmp = ft_strtrim(line, " 	\n");
	while (tmp && tmp[0] != '1')
	{
		free(line);
		if (tmp)
		{
			if (tmp[0] == 'N' && tmp[1] == 'O' && (tmp[2] == SPACE || tmp[2] == TAB))
			{
				free(info->north_path);
				info->north_path = take_diraction_path(tmp);
			}
			else if (tmp[0] == 'S' && tmp[1] == 'O' && (tmp[2] == SPACE || tmp[2] == TAB))
			{
				free(info->south_path);
				info->south_path = take_diraction_path(tmp);
			}
			else if (tmp[0] == 'W' && tmp[1] == 'E' && (tmp[2] == SPACE || tmp[2] == TAB))
			{
				free(info->west_path);
				info->west_path = take_diraction_path(tmp);
			}
			else if (tmp[0] == 'E' && tmp[1] == 'A' && (tmp[2] == SPACE || tmp[2] == TAB))
			{
				free(info->east_path);
				info->east_path = take_diraction_path(tmp);
			}
			else if (tmp[0] == 'F' && (tmp[1] == SPACE || tmp[1] == TAB))
			{
				free(info->f_color);
				info->f_color = take_color(tmp);
			}
			else if (tmp[0] == 'C' && (tmp[1] == SPACE || tmp[1] == TAB))
			{
				free(info->c_color);
				info->c_color = take_color(tmp);
			}
			else if (tmp[0] != '\0')
				ft_error("Invalid information");
		}
		free(tmp);
		line = get_next_line(fd);
		tmp = ft_strtrim(line, " 	\n");
	}
	free(tmp);
	if (info->east_path == NULL || info->north_path == NULL || info->south_path == NULL || info->west_path == NULL)
		ft_error("A texter path is meassing");
	if (info->c_color == NULL || info->f_color == NULL)
		ft_error("Color is missing");
	take_map(info, line, fd);
	return (info);
}

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
		free(line);
		line = get_next_line(fd);
	}
	if (info->arr_map == NULL)
		ft_error("No map");
	check_map(info);
}

int *take_color(char *s_color)
{
	char *tmp;
	int *color;
	int i = 1;
	int start;
	int j = 0;
	int count = 0;
	bool is_n;

	is_n = false;
	tmp = NULL;
	color = ft_calloc(3, sizeof(int));
	if (color == NULL)
		return NULL;
	while (j < 3)
	{
		while (s_color[i] == SPACE || s_color[i] == TAB)
			i++;
		start = i;
		while (s_color[i] && s_color[i] != ',')
		{
			if (s_color[i] == SPACE || s_color[i] == TAB)
			{
				i++;
				continue;
			}
			if (ft_isdigit(s_color[i]) == 0)
				is_n = true;
			else if (s_color[i] == '-' || s_color[i] == '+')
				count++;
			if (count > 1 || (ft_isdigit(s_color[i]) != 0 && s_color[i] != '-' && s_color[i] != '+'))
				ft_error("The color must be a number");
			i++;
		}
		if (is_n)
			tmp = ft_substr(s_color, start, i - 1);
		else
			ft_error("The is no digit before coma");
		color[j] = ft_atoi(tmp);
		printf("color[j] = %d\n", color[j]);
		if (color[j] < 0 || color[j] > 255)
			ft_error("The color number shoud be between [0, 255]");
		is_n = false;
		if (s_color[i])
			i++;
		j++;
		count = 0;
	}
	if (s_color[i] != '\0')
		ft_error("The form of color is x, x, x");
	return (color);
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
	info->player_fov = 114;
	line = get_next_line(fd);
	tmp = ft_strtrim(line, " 	\n");
	while (tmp && tmp[0] != '1')
	{
		free(line);

		if (tmp)
		{
			if (tmp[0] == 'N' && tmp[1] == 'O' && (tmp[2] == SPACE || tmp[2] == TAB))
				info->north_path = take_diraction_path(tmp);
			else if (tmp[0] == 'S' && tmp[1] == 'O' && (tmp[2] == SPACE || tmp[2] == TAB))
				info->south_path = take_diraction_path(tmp);
			else if (tmp[0] == 'W' && tmp[1] == 'E' && (tmp[2] == SPACE || tmp[2] == TAB))
				info->west_path = take_diraction_path(tmp);
			else if (tmp[0] == 'E' && tmp[1] == 'A' && (tmp[2] == SPACE || tmp[2] == TAB))
				info->east_path = take_diraction_path(tmp);
			else if (tmp[0] == 'F' && (tmp[1] == SPACE || tmp[1] == TAB))
				info->f_color = take_color(tmp);
			else if (tmp[0] == 'C' && (tmp[1] == SPACE || tmp[1] == TAB))
				info->c_color = take_color(tmp);
		}
		line = get_next_line(fd);
		tmp = ft_strtrim(line, " 	\n");
	}
	// take_map(info, line, fd);
	return (info);
}

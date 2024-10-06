#include "../includes/parsing.h"

// print Error massege in stderr
void ft_error(char *error_ms)
{
	write(STDERR_FILENO, error_ms, ft_strlen(error_ms));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

static void check_after_map(t_info *info, char *line, int fd)
{
	int i;

	i = 0;
	if (info->arr_map == NULL)
		ft_error("No map");
	line = get_next_line(fd);
	while (line)
	{
		while (line[i] && line[i] != '\n' && (line[i] == SPACE || line[i] == TAB))
			i++;
		if (line[i] != '\n' && line[i] != '\0')
			ft_error("More content after the map");
		free(line);
		line = get_next_line(fd);
	}
	check_map(info);
}

void take_map(t_info *info, char *line, int fd)
{
	int len;
	char *tmp;

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
	check_after_map(info, line, fd);
}

static void check_color_number(char **color_split, int i, int *count)
{
	int j;

	j = 0;
	while (color_split[i] && color_split[i][j])
	{
		if (color_split[i][j] == '-' || color_split[i][j] == '+')
			(*count)++;
		else if (ft_isdigit(color_split[i][j]) == -1)
			ft_error("The color must be a number");
		if (*count > 1)
			ft_error("Invalid color number");
		j++;
	}
}

static void take_color(char **color_split, int **color, char *tmp)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (i < 3)
	{
		tmp = color_split[i];
		color_split[i] = ft_strtrim(color_split[i], "	 ");
		free(tmp);
		check_color_number(color_split, i, &count);
		if (color_split[i] && color_split[i][0])
			(*color)[i] = ft_atoi(color_split[i]);
		else
			ft_error("Invalid color number");
		if ((*color)[i] < 0 || (*color)[i] > 255)
			ft_error("The color number must be in this range [0, 255]");
		count = 0;
		i++;
	}
}

int *take_color_init(char *s_color)
{
	int *color;
	char *tmp;
	char **color_split;

	color = ft_calloc(3, sizeof(int));
	if (color == NULL)
		ft_error("Malloc Flailed");
	tmp = ft_substr(s_color, 1, ft_strlen(s_color));
	color_split = ft_split(tmp, ',');
	free(tmp);
	if (array_length(color_split) > 3)
		ft_error("Invalid color number");
	take_color(color_split, &color, tmp);
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

static void store_path(char *tmp, char c1, char c2, char **path_box)
{
	if (tmp[0] == c1 && tmp[1] == c2 && (tmp[2] == SPACE || tmp[2] == TAB))
	{
		free(*path_box);
		*path_box = take_diraction_path(tmp);
	}
}

static void store_color(char *tmp, char c, int **color_box)
{
	if (tmp[0] == c && (tmp[1] == SPACE || tmp[1] == TAB))
	{
		free(*color_box);
		*color_box = take_color_init(tmp);
	}
}

static bool check_file_char(char c)
{
	char *chars;
	int i;

	chars = "NSWECF";
	while (*chars)
	{
		if (*chars == c)
			return false;
		chars++;
	}
	return true;
}

static void fill_info(char *tmp, t_info *info)
{
	// we can avoid using the paths by assigning directly
	store_path(tmp, 'N', 'O', &info->north_path);
	store_path(tmp, 'S', 'O', &info->south_path);
	store_path(tmp, 'W', 'E', &info->west_path);
	store_path(tmp, 'E', 'A', &info->east_path);
	load_all_textures(&info);
	store_color(tmp, 'C', &info->c_color);
	store_color(tmp, 'F', &info->f_color);
	if (check_file_char(tmp[0]) && tmp[0] != '\0')
		ft_error("Invalid information");
}

// read the .cub file and return it as t_info
t_info *read_info(int fd)
{
	char *line;
	char *tmp;
	char **split_line;
	t_info *info;

	info = ft_calloc(1, sizeof(t_info));
	line = get_next_line(fd);
	tmp = ft_strtrim(line, " 	\n");
	while (tmp && tmp[0] != '1')
	{
		free(line);
		fill_info(tmp, info);
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

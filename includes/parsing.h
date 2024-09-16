
#ifndef PARSING_H
#define PARSING_H

#include "types.h"
//              check.c
bool check_filename(char *file_name);
// bool check_char(char c);
bool check_color(int *color);
void check_map(t_info *info);

//			array
int array_length(char **array);
void free_array(char ***array);
int array_size(char **array);
char **append_array(char **old_array, char *arg);

t_info *read_info(int fd);
void ft_error(char *error_ms);
// bool check_map(char *row);


void put_pixel(t_mlx *mlx, int x, int y, int color);
void display_square(t_mlx mlx, int color, const int x, const int y);
int get_rgba(int r, int g, int b, int a);
void display_map(t_mlx mlx);
void keyhook(mlx_key_data_t keydata, void *param);
void display_window(t_mlx *mlx);


void display_aline(t_mlx mlx);

#endif

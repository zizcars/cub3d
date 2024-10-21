
#ifndef UTILES_H
#define UTILES_H

#include "types.h"

bool check_filename(char *file_name);
bool check_color(int *color);
// void check_map(t_info *info);
void check_map(char **map, int j, int i);
t_info *read_info(int fd);
void put_pixel(mlx_image_t *image, int x, int y, int color);
void display_square(mlx_image_t *image, int color, const int x, const int y);
int get_rgba(int r, int g, int b, int a);
void display_map(t_mlx *mlx);
void keyhook(mlx_key_data_t keydata, void *param);
void display_window(t_mlx *mlx);
double angle_corrector(double angle);
void display_rays(t_mlx mlx);
void free_info(t_info *info);
void draw_floor_ceiling(t_mlx mlx);
int load_all_textures(t_info **);
bool check_char(char c);
void set_player_info(t_info *info, int x, int y);
void mousehook(void *param);
void keyhook(mlx_key_data_t keydata, void *param);
void ft_error(char *error_ms);
void free_array(char ***array);
void display_mini_map_ground(mlx_image_t *img);
void move(t_mlx *mlx, E_DIRECTION d);
void display_person(mlx_image_t *img, const int x, const int y);
char **append_array(char **old_array, char *arg);
int array_length(char **array);

#endif

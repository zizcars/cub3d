
#ifndef UTILES_H
#define UTILES_H

#include "types.h"

bool check_filename(char *file_name);
bool check_color(int *color);
void check_map(t_info *info);
t_info *read_info(int fd);
void put_pixel(mlx_image_t *image, int x, int y, int color);
void display_square(mlx_image_t *image, int color, const int x, const int y);
int get_rgba(int r, int g, int b, int a);
void display_mini_map(t_mlx *mlx);
void display_window(t_mlx *mlx);
double angle_corrector(double angle);
void display_rays(t_mlx mlx);
void free_info(t_info *info);
void draw_floor_ceiling(t_mlx mlx);
int load_all_textures(t_info **);
bool check_char(char c);
void set_player_info(t_info *info, int x, int y, int *count);
void mousehook(void *param);
void keyhook(void *param);
void ft_error(char *error_ms);
void free_array(char ***array);
void display_mini_map_ground(mlx_image_t *img);
void move(t_mlx *mlx, E_DIRECTION d);
void display_person(mlx_image_t *img, const int x, const int y);
char **append_array(char **old_array, char *arg);
int array_length(char **array);
void update_map(t_mlx *mlx);
void render3d(t_mlx mlx, t_point *x);
int get_color(mlx_texture_t *texture, int x, int y);
t_point *calculate_horizontal_intersection(t_mlx mlx, double angle);
t_point *calculate_vertical_intersection(t_mlx mlx, const double angle);
void store_color(char *tmp, char c, int **color_box);
void store_path(char *tmp, char c1, char c2, char **path_box);
void take_map(t_info *info, char *line, int fd);
bool	move_check(t_mlx mlx, int nx, int ny);

#endif

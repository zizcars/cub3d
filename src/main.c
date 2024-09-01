
#include "../includes/parsing.h"

void print_info(t_map_info *info)
{
    printf("North path: %s\n", info->north_path);
    printf("South path: %s\n", info->south_path);
    printf("West path: %s\n", info->west_path);
    printf("East path: %s\n", info->east_path);
    printf("Floor color: %s\n", info->floor_color);
    printf("Ceiling color: %s\n", info->ceiling_color);
    printf("MAP: \n");
    for (int i = 0; info->arr_map[i]; i++)
    {
        printf("|%s|\n", info->arr_map[i]);
    }
    // int i = 0;
    // int j;
    // while(info->map && info->map[i])
    // {
    //     j = 0;
    //     while(info->map[i][j])
    //         printf("%c", info->map[i][j++]);
    //     printf("\n");
    //     i++;
    // }
}

// solve the problem of space between i information like F 32,   34, 343
// check the number of players and other characters in the map
#define W 255
#define H 255

int main()
{
    // t_map_info *info;
    // int fd;

    // fd = open("maps/map.cub", O_RDONLY);
    // if (fd < 0)
    //     printf("no file\n");
    // info = read_info(fd);

    // close (fd);
    mlx_t *mlx;
    mlx_image_t *mlx_im;
    mlx = mlx_init(W, H, "window", true);
    mlx_im = mlx_new_image(mlx, W, H);
    for(int i = 0; i < 100; i++)
    {
        mlx_put_pixel(mlx_im, i , i, 100);
    }

    mlx_image_to_window(mlx, mlx_im, 0, 0);
    mlx_loop(mlx);
}
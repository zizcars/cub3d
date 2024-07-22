
#include "parsing.h"


void print_info(t_map_info *info)
{
    printf("North path: %s\n", info->north_path);
    printf("South path: %s\n", info->south_path);
    printf("West path: %s\n", info->west_path);
    printf("East path: %s\n", info->east_path);
    printf("Floor color: %s\n", info->floor_color);
    printf("Ceiling color: %s\n", info->ceiling_color);
    printf("map:\n%s", info->map);
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

int main()
{
    t_map_info *info;
    int fd;

    fd = open("map.cub", O_RDONLY);
    info = read_info(fd);
    print_info(info);
    close (fd);

    // if (check_char(argv[1][0]))
    //     printf("char: %c\tvalid\n", argv[1][0]);
    // else   
    //     printf("char: %c\tinvalid\n", argv[1][0]);

}
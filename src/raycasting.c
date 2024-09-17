#include "../includes/types.h"
#include "../includes/parsing.h"

#define NUM_RAYS 25



//The distance to the first object (wall, etc.) each ray encounters.
// Information about where the intersection happens, like coordinates or wall type, to use for further logic or rendering.

// Change the ray casting for calcule every point to calculate just the start and end of a block
void display_rays(t_mlx mlx)
{
    float startAngle = mlx.info->player_angle - mlx.info->player_fov / 2;
    float endAngle = mlx.info->player_angle + mlx.info->player_fov / 2;
    // float deltaX;
    // float deltaY;
    for (int i = 0; i < NUM_RAYS; i++)
    {
        // Calculate the current angle
        // printf("hi\n");
        float angle = startAngle + i * (endAngle - startAngle) / (NUM_RAYS - 1);

        // Convert the angle from degrees to radians
        // printf("mlx.info->player_angle:%f\tmlx.info->player_fov:%f\n", mlx.info->player_angle, mlx.info->player_fov);
        // printf("startAngle:%f\endAngle:%f\n", startAngle, endAngle);
        float radAngle = angle * M_PI / 180.0f;

        // Calculate the ray endpoint
        // printf("radAngle:%f\n", radAngle);
        // float rayX = mlx.info->player_x + cosf(radAngle) * 40;
        // float rayY = mlx.info->player_y + sinf(radAngle) * 40;
        // printf("RayX:%f\tRayY:%f\n", rayX, rayY);
        // printf("height:%d\twidth:%d\n", mlx.info->height * SIZE, mlx.info->width * SIZE);
        // printf("player_x:%d\tplayer_y:%d\n", mlx.info->player_x, mlx.info->player_y);
        float x = mlx.info->player_x;
        float y = mlx.info->player_y;
        int k = 0;
        // while (y != rayY)
        while(mlx.info->arr_map[(int)y/SIZE][(int)x/SIZE] != '1')
        {
            x = mlx.info->player_x + cosf(radAngle) * k;
            y = mlx.info->player_y + sinf(radAngle) * k;
            // printf("X:%f\tY:%f\n", x, y);
            mlx_put_pixel(mlx.image, x, y, get_rgba(255, 0, 0, 255));
            k++;
        }
        // while (y == rayY && x != rayX)
        // {
        //     x = mlx.info->player_x + cosf(radAngle) * k;
        //     mlx_put_pixel(mlx.image, x, y, get_rgba(255, 0, 0, 255));
        //     k++;
        // }

        // mlx_put_pixel(mlx.image, rayX, rayY, get_rgba(255, 0, 255, 255));
    }
}
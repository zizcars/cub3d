#include "../includes/types.h"
#include "../includes/parsing.h"

#define NUM_RAYS 900 // should be width of the window

// The distance to the first object (wall, etc.) each ray encounters.
//  Information about where the intersection happens, like coordinates or wall type, to use for further logic or rendering.

// Change the ray casting for calcule every point to calculate just the start and end of a block
void display_rays(t_mlx mlx)
{
    float startAngle = mlx.info->player_angle - mlx.info->player_fov / 2;
    float endAngle = mlx.info->player_angle + mlx.info->player_fov / 2;
    for (int i = 0; i < NUM_RAYS; i++)
    {
        float angle = startAngle + i * (endAngle - startAngle) / NUM_RAYS;
        float radAngle = angle * M_PI / 180.0f;
        float x = mlx.info->player_x;
        float y = mlx.info->player_y;
        while (mlx.info->arr_map[(int)y / SIZE][(int)x / SIZE] != '1')
        {
            x += cosf(radAngle); // tells you how much to move horizontally to stay in that direction.
            y += sinf(radAngle); // tells you how much to move vertically to stay in that direction.
            mlx_put_pixel(mlx.image, x, y, get_rgba(RAYS_COLOR, 255));
        }
    }
}

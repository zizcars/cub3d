#include "../includes/types.h"
#include "../includes/parsing.h"

#define NUM_RAYS 900 // should be width of the window

// The distance to the first object (wall, etc.) each ray encounters.
//  Information about where the intersection happens, like coordinates or wall type, to use for further logic or rendering.

// Change the ray casting for calcule every point to calculate just the start and end of a block
void display_rays(t_mlx mlx)
{
	float start_angle = mlx.info->player_angle - mlx.info->player_fov / 2;
	float end_angle = mlx.info->player_angle + mlx.info->player_fov / 2;
	float angle = start_angle;
	int r = 0;
	float x, y, xa, ya, xb, yb;
	float d1, d2;
    d1 = 99999999;
    d2 = 99999999;
	while (r < NUM_RAYS)
	{
		angle = start_angle + r * mlx.info->player_fov / NUM_RAYS;
		// angle = angle * M_PI / 180.0f;
		if (angle < M_PI && angle > 0)
			ya = floor(mlx.info->player_y / SIZE) * SIZE + SIZE;
		else
			ya = floor(mlx.info->player_y / SIZE) * SIZE - 1;
		if (fabs(tan(angle)) > 0.0001)
			xa = (ya - mlx.info->player_y) / tan(angle) + mlx.info->player_x;
		while (xa > 0 && xa < mlx.info->width * SIZE && ya > 0 && ya < mlx.info->height * SIZE)
		{
			printf("(%f,%f) [%d, %d] H:%d W:%d\n", xa, ya, (int)xa / SIZE, (int)ya / SIZE, mlx.info->height * SIZE, mlx.info->width * SIZE);
			if (mlx.info->arr_map[(int)ya / SIZE][(int)xa / SIZE] == '1' || mlx.info->arr_map[(int)ya / SIZE][(int)xa / SIZE] == '\0')
				break;
    		if (angle < M_PI && angle > 0)
				y = SIZE;
			else
				y = -SIZE;
			if (fabs(tan(angle)) > 0.0001)
				x = y / tan(angle);
			xa += x;
			ya += y;
		}
		// if (angle < (3 * M_PI) / 2 && angle > M_PI / 2)
		// 	xb = floor(mlx.info->player_x / SIZE) * SIZE + SIZE;
		// else
		// 	xb = floor(mlx.info->player_x / SIZE) * SIZE - 1;
		// if (fabs(cos(angle)) >= 0.0001)
		// 	yb = mlx.info->player_y + (mlx.info->player_x - xb) * tan(angle);
		// else
		// 	yb = mlx.info->player_y + (mlx.info->player_x - xb);
		// while (xb > 0 && xb < mlx.info->width * SIZE && yb > 0 && yb < mlx.info->height * SIZE)
		// {
		// 	// printf("(%f, %f)\n", xb/SIZE, yb/SIZE);
		// 	// mlx_put_pixel(mlx.r_image, xb, yb, get_rgba(0, 255, 0, 255));
		// 	if (mlx.info->arr_map[(int)yb / SIZE][(int)xb / SIZE] == '1' || mlx.info->arr_map[(int)yb / SIZE][(int)xb / SIZE] == '\0')
		// 		break;
		// 	if (angle < (3 * M_PI) / 2 && angle > M_PI / 2)
		// 		x = SIZE;
		// 	else
		// 		x = -SIZE;
		// 	if (fabs(cos(angle)) >= 0.0001)
		// 		y = x * tan(angle);
		// 	// else
		// 	// 	y = x;
		// 	xb += x;
		// 	yb += y;
		// }
		// d1 = sqrt(pow(mlx.info->player_x - xa, 2) + pow(mlx.info->player_y - ya, 2));
		// d2 = sqrt(pow(mlx.info->player_x - xb, 2) + pow(mlx.info->player_y - yb, 2));
		if (xa > 0 && xa < mlx.info->width * SIZE && ya > 0 && ya < mlx.info->height * SIZE)
		    mlx_put_pixel(mlx.r_image, xa, ya, get_rgba(255, 0, 0, 255));
		// if (xb > 0 && xb < mlx.info->width * SIZE && yb > 0 && yb < mlx.info->height * SIZE)
		// 	mlx_put_pixel(mlx.r_image, xb, yb, get_rgba(0, 255, 0, 255));
        
		// if (xa > 0 && xa < mlx.info->width * SIZE && ya > 0 && ya < mlx.info->height * SIZE)
		// 	mlx_put_pixel(mlx.r_image, xa, ya, get_rgba(255, 0, 0, 255));
		r++;
	}
	// printf("------------------------------\n");
}

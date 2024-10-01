#include "../includes/types.h"
#include "../includes/parsing.h"

#define NUM_RAYS 1000 // should be width of the window

// The distance to the first object (wall, etc.) each ray encounters.
// Information about where the intersection happens, like coordinates or wall type, to use for further logic or rendering.

// Change the ray casting for calcule every point to calculate just the start and end of a block
static bool is_gape(char **map, int x, int y, int nx, int ny)
{
	if (map[ny][nx] == '1' || map[ny][nx] == '\0' || map[ny][nx] == SPACE)
		return true;
	else if (map[ny][x] == '1' && map[y][nx] == '1')
		return true;
	return false;
}

t_point *calculate_horizontal_intersection(t_mlx mlx, double angle)
{
	double x;
	double y;
	t_point *a;
	int tx, ty;

	a = ft_calloc(1, sizeof(t_point));
	if (a == NULL)
		ft_error("malloc faild");
	if (angle <= M_PI && angle >= 0)
		a->y = floor(mlx.info->player_y / SIZE) * SIZE + SIZE;
	else
		a->y = floor(mlx.info->player_y / SIZE) * SIZE - 0.00001;
	a->x = (a->y - mlx.info->player_y) / tan(angle) + mlx.info->player_x;
	tx = a->x;
	ty = a->y;
	while (a->x > 0 && a->x < mlx.info->width * SIZE && a->y > 0 && a->y < mlx.info->height * SIZE)
	{
		if (is_gape(mlx.info->arr_map, tx / SIZE, ty / SIZE, a->x / SIZE, a->y / SIZE))
			break;
		if (angle <= M_PI && angle >= 0)
			y = SIZE;
		else
			y = -SIZE;
		x = y / tan(angle);
		tx = a->x;
		ty = a->y;
		a->x += x;
		a->y += y;
	}
	if (a->x > 0 && a->x < mlx.info->width * SIZE && a->y > 0 && a->y < mlx.info->height * SIZE)
		a->distance = sqrt(pow(mlx.info->player_x - a->x, 2) + pow(mlx.info->player_y - a->y, 2));
	else
		a->distance = 2147483647;
	return a;
}

t_point *calculate_vertical_intersection(t_mlx mlx, const float angle)
{
	float x, y;
	t_point *a;
	int tx, ty;

	a = ft_calloc(1, sizeof(t_point));
	if (a == NULL)
		ft_error("malloc faild");
	if (angle <= (3 * M_PI) / 2 && angle >= M_PI / 2) // left
		a->x = (mlx.info->player_x / SIZE) * SIZE - 0.00001;
	else
		a->x = (mlx.info->player_x / SIZE) * SIZE + SIZE;
	a->y = mlx.info->player_y + (a->x - mlx.info->player_x) * tan(angle);
	tx = a->x;
	ty = a->y;
	while (a->x > 0 && a->x < mlx.info->width * SIZE && a->y > 0 && a->y < mlx.info->height * SIZE)
	{
		if (is_gape(mlx.info->arr_map, tx / SIZE, ty / SIZE, a->x / SIZE, a->y / SIZE))
			break;
		if (angle <= (3 * M_PI) / 2 && angle >= M_PI / 2) // left
			x = -SIZE;
		else
			x = SIZE;
		y = x * tan(angle);
		tx = a->x;
		ty = a->y;
		a->x += x;
		a->y += y;
	}
	if (a->x > 0 && a->x < mlx.info->width * SIZE && a->y > 0 && a->y < mlx.info->height * SIZE)
		a->distance = sqrt(pow(mlx.info->player_x - a->x, 2) + pow(mlx.info->player_y - a->y, 2));
	else
		a->distance = 2147483647;
	return a;
}

void render(t_mlx *mlx, int d, int r, double a)
{
	int line_h;
	printf("%d ", d);
	if (d)
		line_h = (64.0 / d) * 277;
	else
		line_h = 0;
	int draw_begin = (HEIGHT / 2) - (line_h / 2);
	int draw_end = draw_begin + line_h;
	printf("line_h = %d, draw B = %d, draw e = %d\n", line_h, draw_begin, draw_end);
	for (int y = draw_begin; y < draw_end; y += 1)
		mlx_put_pixel(mlx->map_image, r, y, get_rgba(255, 0, 0, 255));
}

void display_rays(t_mlx *mlx)
{
	double start_angle = angle_corrector(mlx->info->player_angle - PLAYER_FOV / 2);
	double angle = start_angle;
	t_point *a;
	t_point *b;
	int r = 0;
	int d;
	mlx_delete_image(mlx->mlx, mlx->map_image);
	mlx->map_image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	while (r < NUM_RAYS)
	{
		angle = angle_corrector(start_angle + r * PLAYER_FOV / NUM_RAYS);
		a = calculate_horizontal_intersection(*mlx, angle);
		b = calculate_vertical_intersection(*mlx, angle);
		if (a->x > 0 && a->x < mlx->info->width * SIZE && a->y > 0 && a->y < mlx->info->height * SIZE && a->distance < b->distance)
			d = a->distance;
		// mlx_put_pixel(mlx->r_image, a->x, a->y, get_rgba(255, 0, 0, 255));
		else if (b->x > 0 && b->x < mlx->info->width * SIZE && b->y > 0 && b->y < mlx->info->height * SIZE && a->distance >= b->distance)
			d = b->distance;
		// mlx_put_pixel(mlx->r_image, b->x, b->y, get_rgba(0, 255, 0, 255));
		free(a);
		free(b);
		render(mlx, d, r, angle);
		r++;
	}
	mlx_image_to_window(mlx->mlx, mlx->map_image, 0, 0);
}

// void display_rays(t_mlx mlx)
// {
//     float startAngle = mlx.info->player_angle - mlx.info->player_fov / 2;
//     float endAngle = mlx.info->player_angle + mlx.info->player_fov / 2;
//     int d;

//     for (int i = 0; i < NUM_RAYS; i++)
//     {
//         float angle = startAngle + i * (endAngle - startAngle) / NUM_RAYS;
//         // float radAngle = angle * M_PI / 180.0f;
//         float x = mlx.info->player_x;
//         float y = mlx.info->player_y;
//         while (1)
//         {
//             if (x < 0 || x >= mlx.info->width * SIZE || y < 0 || y >= mlx.info->height * SIZE)
//                 break;
//             if (mlx.info->arr_map[(int)y / SIZE][(int)x / SIZE] == '1' || mlx.info->arr_map[(int)y / SIZE][(int)x / SIZE] == '\0' || mlx.info->arr_map[(int)y / SIZE][(int)x / SIZE] == SPACE)
//                 break;
//             x += cosf(angle); // tells you how much to move horizontally to stay in that direction.
//             y += sinf(angle); // tells you how much to move vertically to stay in that direction.
//             mlx_put_pixel(mlx.r_image, x, y, get_rgba(RAYS_COLOR, 255));
//         }
//         d = sqrt(pow(x - mlx.info->player_x, 2) + pow(y - mlx.info->player_y, 2));
//     }
// }

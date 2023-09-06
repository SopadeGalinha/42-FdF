#include "../includes/fdf.h"

float mod(float a)
{
    return (a < 0 ? -a : a);
}

int print_keycode(int key, void *param)
{
    if (key < 0)
        param = NULL;
    if (key == 65307)
        exit(0);
    printf("key: %d\n", key);
    return (0);
}

void set_axis(float *axis, int x, int y, bool line)
{
    axis[START_X] = x;
    axis[START_Y] = y;
    axis[END_X] = x;
    axis[END_Y] = y + 1;
    if (line)
        axis[END_X] = x + 1;
    if (line)
        axis[END_Y] = y;
}

#define ISOMETRIC_ANGLE 0.523599

void apply_isometric(t_fdf *fdf, float *axis) {
    float prev_x = axis[START_X];
    float prev_y = axis[START_Y];

    axis[START_X] = (prev_x - prev_y) * cos(ISOMETRIC_ANGLE);
    axis[START_Y] = -axis[START_Z] + (prev_x + prev_y) * sin(ISOMETRIC_ANGLE);

    float center_x = fdf->map->max_x * 0.5;
    float center_y = fdf->map->max_y * 0.5;

    axis[START_X] += center_x;
    axis[START_Y] += center_y;

    prev_x = axis[END_X];
    prev_y = axis[END_Y];

    axis[END_X] = (prev_x - prev_y) * cos(ISOMETRIC_ANGLE);
    axis[END_Y] = -axis[END_Z] + (prev_x + prev_y) * sin(ISOMETRIC_ANGLE);

    axis[END_X] += center_x;
    axis[END_Y] += center_y;
}

// Function to draw a line using Bresenham's algorithm
void draw_line(t_fdf *fdf, float *axis, int color) {
    float step_x = axis[END_X] - axis[START_X];
    float step_y = axis[END_Y] - axis[START_Y];
    int max = MAX(mod(step_x), mod(step_y));

    step_x /= max;
    step_y /= max;

    while ((int)(axis[START_X] - axis[END_X]) || (int)(axis[START_Y] - axis[END_Y])) {
        mlx_pixel_put(fdf->mlx, fdf->window, axis[START_X], axis[START_Y], color);
        axis[START_X] += step_x;
        axis[START_Y] += step_y;
    }
}

// Function to draw the map

void draw_map(t_fdf *fdf) {
    int x, y;
    float axis[4];
    int color;
    int center_x = (fdf->map->max_x * fdf->map->zoom) / 2;
    int center_y = (fdf->map->max_y * fdf->map->zoom) / 2;

    y = -1;
    while (++y < fdf->map->max_y) {
        x = -1;
        while (++x < fdf->map->max_x) {
            color = fdf->map->coordinates[y][x].color;

            // Calculate position with zoom and centralization
            axis[START_X] = x * fdf->map->zoom - center_x + (fdf->window_width / 2);
            axis[START_Y] = y * fdf->map->zoom - center_y + (fdf->window_height / 2);
            axis[END_X] = (x + 1) * fdf->map->zoom - center_x + (fdf->window_width / 2);
            axis[END_Y] = y * fdf->map->zoom - center_y + (fdf->window_height / 2);

            // Apply isometric projection
            apply_isometric(fdf, axis);

            if (x + 1 < fdf->map->max_x)
                draw_line(fdf, axis, color);

            axis[START_X] = x * fdf->map->zoom - center_x + (fdf->window_width / 2);
            axis[START_Y] = y * fdf->map->zoom - center_y + (fdf->window_height / 2);
            axis[END_X] = x * fdf->map->zoom - center_x + (fdf->window_width / 2);
            axis[END_Y] = (y + 1) * fdf->map->zoom - center_y + (fdf->window_height / 2);

            // Apply isometric projection
            apply_isometric(fdf, axis);

            if (y + 1 < fdf->map->max_y)
                draw_line(fdf, axis, color);
        }
    }
}

void	set_window(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	mlx_get_screen_size(fdf->mlx, &(fdf->window_width), &(fdf->window_height));
	fdf->window_width = fdf->window_width * 0.5;
	fdf->window_height = fdf->window_width * 0.6;
	fdf->window = mlx_new_window(fdf->mlx, fdf->window_width, \
	fdf->window_height, WINDOW_NAME);
}

void set_pivot(t_fdf *fdf) {
    int x, y;
    int sum_x = 0;
    int sum_y = 0;

    // Calculate the sum of all x and y coordinates
    for (y = 0; y < fdf->map->max_y; y++) {
        for (x = 0; x < fdf->map->max_x; x++) {
            sum_x += fdf->map->coordinates[y][x].x;
            sum_y += fdf->map->coordinates[y][x].y;
        }
    }

    // Calculate the center based on the window size
    int center_x = fdf->window_width / 2;
    int center_y = fdf->window_height / 2;

    // Adjust the coordinates based on the center
    for (y = 0; y < fdf->map->max_y; y++) {
        for (x = 0; x < fdf->map->max_x; x++) {
            fdf->map->coordinates[y][x].x -= sum_x / (fdf->map->max_x * fdf->map->max_y);
            fdf->map->coordinates[y][x].y -= sum_y / (fdf->map->max_x * fdf->map->max_y);
        }
    }
}



void	set_limits_end(float *axis, t_fdf *fdf)
{
	int	y;
	int	x;
	
	y = -1;
	while (++y < fdf->map->max_y)
	{
		x = -1;
		while (++x < fdf->map->max_x)
		{
			if (axis[END_X] < fdf->map->coordinates[y][x].x)
				axis[END_X] = fdf->map->coordinates[y][x].x;
			if (axis[END_Y] < fdf->map->coordinates[y][x].y)
				axis[END_Y] = fdf->map->coordinates[y][x].y;
			if (axis[END_Z] < fdf->map->coordinates[y][x].z)
				axis[END_Z] = fdf->map->coordinates[y][x].z;
		}
	}
}	

void	set_limits_aux(float *axis, t_fdf *fdf)
{
	int	y;
	int	x;
	
	y = -1;
	while (++y < fdf->map->max_y)
	{
		x = -1;
		while (++x < fdf->map->max_x)
		{
			if (axis[START_X] > fdf->map->coordinates[y][x].x)
				axis[START_X] = fdf->map->coordinates[y][x].x;
			if (axis[START_Y] > fdf->map->coordinates[y][x].y)
				axis[START_Y] = fdf->map->coordinates[y][x].y;
			if (axis[START_Z] > fdf->map->coordinates[y][x].z)
				axis[START_Z] = fdf->map->coordinates[y][x].z;
		}
	}
	set_limits_end(axis, fdf);
}

void	set_zoom(t_fdf *fdf, float *axis)
{
	float	zoom_x;
	float	zoom_y;
	float	zoom_z;
	float	zoom;
	
	zoom_x = fdf->window_width / (axis[END_X] - axis[START_X]);
	zoom_y = fdf->window_height / (axis[END_Y] - axis[START_Y]);
	if (fabsf(axis[END_Z]) > fabsf(axis[START_Z]))
		zoom_z = fdf->window_height / fabsf(axis[END_Z]);
	else
		zoom_z = fdf->window_height / fabsf(axis[START_Z]);
	zoom = MIN(zoom_x, zoom_y);
	fdf->map->zoom = MIN(zoom, zoom_z);
	fdf->map->zoom = fdf->map->zoom * 0.8;
}

void	set_limits(t_fdf *fdf)
{
	float	axis[6];
	
	axis[START_X] = (float)INT_MAX;
	axis[START_Y] = (float)INT_MAX;
	axis[START_Z] = (float)INT_MAX;
	axis[END_X] = (float)INT_MIN;
	axis[END_Y] = (float)INT_MIN;
	axis[END_Z] = (float)INT_MIN;
	set_limits_aux(axis, fdf);
 	fdf->map->max_x = axis[END_X] - axis[START_X];
	fdf->map->max_y = axis[END_Y] - axis[START_Y];
	fdf->map->max_z = axis[END_Z] - axis[START_Z];
	fdf->map->min_z = axis[START_Z];
 
	set_zoom(fdf, axis);
}

void render(t_fdf *fdf)
{
	set_window(fdf);
	set_pivot(fdf);
	set_limits(fdf);
	draw_map(fdf);
	mlx_key_hook(fdf->window, print_keycode, NULL);
	mlx_loop(fdf->mlx);

}

int	main(int ac, char **av)
{
	t_fdf	fdf;
	if (ac != 2)
		return (write(1, "Error: Invalid number of arguments\n", 35));
	fdf = (t_fdf){.map = &(t_map){.coordinates = &(t_point *){0}}};
	ft_initialization(&fdf, av[1]);
	if (!fdf.error_message)
		render(&fdf);
	else
		printf("error_message: %s\n", fdf.error_message);
	return (0);
}

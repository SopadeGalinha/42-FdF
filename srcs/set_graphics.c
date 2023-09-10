#include "../includes/fdf.h"

void initialize_zoom(t_fdf *fdf)
{
	float zoom;
	float sizes[3];

	sizes[0] = WINX * 0.5f / fdf->limits.max_x;
	sizes[1] = WINY * 0.5f / fdf->limits.max_y;
	if (fabsf(fdf->limits.min_z) > fdf->limits.max_z)
		sizes[2] = WINY * 0.5f / fabsf(fdf->limits.min_z) * 0.8f;
	else
		sizes[2] = WINY * 0.5f / fdf->limits.max_z * 0.8f;
	zoom = (float)INT_MAX;
	if (sizes[0] < zoom)
		zoom = sizes[0];
	if (sizes[1] < zoom)
		zoom = sizes[1];
	if (sizes[2] < zoom)
		zoom = sizes[2];
	fdf->zoom = zoom * 0.8f;
}

void	set_graphics(t_fdf *fdf)
{
	fdf->offset = (t_points){WINX / 2, WINY / 2};
	fdf->colors = fdf->color;
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WINX, WINY, "FdF");
	initialize_zoom(fdf);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:18:23 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/30 00:53:45 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

float mod(float a)
{
	return (a < 0 ? -a : a);
}

int	print_keycode(int key, void *param)
{
	if (key < 0)
		param = NULL;
	if (key == 65307)
		exit(0);
	printf("key: %d\n", key);
	return (0);
}

void apply_isometric(float *x, float *y, int z)
{
    *x = (*x - *y) * cos(0.523599);
    *y = (*x + *y) * sin(0.523599) - z;
}

void bresenham(float x_iso, float y_iso, float x1_iso, float y1_iso, t_fdf *fdf, int color)
{
	float step[2];
	int max;

	step[POS_X] = x1_iso - x_iso;
	step[POS_Y] = y1_iso - y_iso;
	
	max = MAX(mod(step[POS_X]), mod(step[POS_Y]));
	step[POS_X] /= max;
	step[POS_Y] /= max;

	while ((int)(x_iso - x1_iso) || (int)(y_iso - y1_iso))
	{
		mlx_pixel_put(fdf->mlx, fdf->window, x_iso, y_iso, color);
		x_iso += step[POS_X];
		y_iso += step[POS_Y];
	}
}


void center_grid(int x, int y, t_fdf *fdf, int *start, int *end)
{
	start[POS_X] = (x - (fdf->map->max_x / 2)) * fdf->map->zoom + (fdf->window_width / 2);
	start[POS_Y] = (y - (fdf->map->max_y / 2)) * fdf->map->zoom + (fdf->window_height / 2);
	end[POS_X] = (x + 1 - (fdf->map->max_x / 2)) * fdf->map->zoom + (fdf->window_width / 2);
	end[POS_Y] = (y + 1 - (fdf->map->max_y / 2)) * fdf->map->zoom + (fdf->window_height / 2);
}

void draw(t_fdf *fdf)
{
	int x;
	int y;
	int start[2];
	int end[2];

	y = -1;
	while (++y < fdf->map->max_y)
	{
		x = -1;
		while (++x < fdf->map->max_x)
		{
			center_grid(x, y, fdf, start, end);
			if (x < fdf->map->max_x - 1)
				bresenham(start[POS_X], start[POS_Y], end[POS_X], start[POS_Y], fdf, fdf->map->coordinates[y][x].color);
			if (y < fdf->map->max_y - 1)
				bresenham(start[POS_X], start[POS_Y], start[POS_X], end[POS_Y], fdf, fdf->map->coordinates[y][x].color);
		}
	}
}

void render(t_fdf *fdf)
{
	fdf->window = mlx_new_window(fdf->mlx, fdf->window_width, fdf->window_height, WINDOW_NAME);
	fdf->map->zoom = MIN(fdf->window_width / fdf->map->max_x, fdf->window_height / fdf->map->max_y);
	draw(fdf);
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

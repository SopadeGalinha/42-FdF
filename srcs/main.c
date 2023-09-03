/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:18:23 by jhogonca          #+#    #+#             */
/*   Updated: 2023/09/02 17:40:16 by jhoonca          ###   ########.fr       */
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

void	set_axis(float *axis, int x, int y, bool line)
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

void	isometric(t_fdf *fdf, float *axis)
{
	float	previous_x;
	float	previous_y;

	previous_x = axis[START_X];
	previous_y = axis[START_Y];
	axis[START_X] = (previous_x - previous_y) * cos(0.523599);
	axis[START_Y] = -axis[START_Z] + (previous_x + previous_y) * sin(0.523599);
	previous_x = axis[END_X];
	previous_y = axis[END_Y];
	axis[END_X] = (previous_x - previous_y) * cos(0.523599);
	axis[END_Y] = -axis[END_Z] + (previous_x + previous_y) * sin(0.523599);
}

void	put_axis(t_fdf *fdf, float *axis, int color)
{
	axis[START_X] += fdf->window_width / 2;
	axis[START_Y] += fdf->window_height / 2;
	axis[END_X] += fdf->window_width / 2;
	axis[END_Y] += fdf->window_height / 2;
}

void	brasenham(t_fdf *fdf, float *axis, int color)
{
	float	step_x;
	float	step_y;
	int		max;

	axis[START_Z] = fdf->map->coordinates[(int)axis[START_Y]][(int)axis[START_X]].z;
	axis[END_Z] = fdf->map->coordinates[(int)axis[END_Y]][(int)axis[END_X]].z;
	
	//zoom
	axis[START_X] *= fdf->map->zoom;
	axis[START_Y] *= fdf->map->zoom;
	axis[END_X] *= fdf->map->zoom;
	axis[END_Y] *= fdf->map->zoom;
	
	isometric(fdf, axis);
	put_axis(fdf, axis, color);
	
	step_x = axis[END_X] - axis[START_X];
	step_y = axis[END_Y] - axis[START_Y];
	max = MAX(mod(step_x), mod(step_y));
	step_x /= max;
	step_y /= max;
	while ((int)(axis[START_X] - axis[END_X]) || (int)(axis[START_Y] - axis[END_Y]))
	{
		mlx_pixel_put(fdf->mlx, fdf->window, axis[START_X], axis[START_Y], color);
		axis[START_X] += step_x;
		axis[START_Y] += step_y;
	}
}

void	draw(t_fdf *fdf)
{
	int x;
	int y;
	float	axis[4];
	int		color;

	y = -1;
	
	while (++y < fdf->map->max_y)
	{
		x = -1;
		while (++x < fdf->map->max_x)
		{
			color = fdf->map->coordinates[y][x].color;
			if (x < fdf->map->max_x - 1){
				set_axis(axis, x, y, true);
				brasenham(fdf, axis, color);
			}
			if (y < fdf->map->max_y - 1){
				set_axis(axis, x, y, false);
				brasenham(fdf, axis, color);	
			}
		}
	}
}

void render(t_fdf *fdf)
{
	fdf->window = mlx_new_window(fdf->mlx, fdf->window_width, fdf->window_height, WINDOW_NAME);
	fdf->map->zoom = 15;//MIN(fdf->window_width / fdf->map->max_x, fdf->window_height / fdf->map->max_y);
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

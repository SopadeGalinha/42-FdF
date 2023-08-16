/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:18:23 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/16 22:00:19 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

float mod(float a)
{
	return (a < 0 ? -a : a);
}

void	bresenham(float x, float y, float x1, float y1, t_fdf *fdf)
{
	float	x_step;
	float	y_step;
	int		max;
	int		z;
	int		z1;
	char *color;
	
	z = fdf->map->coordinates[(int)y][(int)x].z;
	z1 = fdf->map->coordinates[(int)y1][(int)x1].z;
	
	x *= fdf->map->zoom;
	y *= fdf->map->zoom;
	x1 *= fdf->map->zoom;
	y1 *= fdf->map->zoom;
			
	color = (z) > 0 ? "16750835" : "9083482";
	
	x_step = x1 - x;
	y_step = y1 - y;
		
	x += 150;
	y += 150;
	x1 += 150;
	y1 += 150;
	
	max = MAX(mod(x_step), mod(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(fdf->mlx, fdf->window, x, y, ft_atoi_base(color, 16));
		x += x_step;
		y += y_step;
	}
}

int	print_keycode(int key, void *param)
{
	if (key < 0)
		param = NULL;
	printf("key: %d\n", key);
	return (0);
}

void	draw(t_fdf *fdf)
{
	int	y;
	int	x;
	
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, fdf->window_width, fdf->window_height, WINDOW_NAME);
	fdf->map->zoom = 20;
	y = -1;
	while (++y < fdf->map->max_y)
	{
		x = -1;
		while (++x < fdf->map->max_x)
		{
			if (x < fdf->map->max_x - 1)
				bresenham(x, y, x + 1, y, fdf);
			if (y < fdf->map->max_y - 1)
				bresenham(x, y, x, y + 1, fdf);
		}
		
	}
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
		draw(&fdf);
	else
		printf("error_message: %s\n", fdf.error_message);
	return (0);
}

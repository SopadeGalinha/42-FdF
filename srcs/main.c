/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:18:23 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/12 22:23:16 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	print_colors(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map->max_y)
	{
		j = 0;
		while (j < fdf->map->max_x)
		{
			printf("%d ", fdf->map->coordinates[i][j].color);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	print_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map->max_y)
	{
		j = 0;
		while (j < fdf->map->max_x)
		{
			if (fdf->map->coordinates[i][j].z > 0)
			{
				printf("\033[0;31m");
				printf("% 3d", (int)fdf->map->coordinates[i][j].z);
				printf("\033[0m");
			}
			else if (fdf->map->coordinates[i][j].z < 0)
			{
				printf("\033[0;34m");
				printf("% 3d", (int)fdf->map->coordinates[i][j].z);
				printf("\033[0m");
			}
			else
				printf("% 3d", (int)fdf->map->coordinates[i][j].z);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	bresenham(float x, float y, float x1, float y1, t_fdf *fdf)
{
	float	step_x;
	float	step_y;
	int		max;
	
	step_x = x1 - x;
	step_y = y1 - y;
	
	max = MAX(MOD(step_x), MOD(step_y));
	step_x /= max;
	step_y /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(fdf->mlx, fdf->window, x, y, 0xFFFFFF);
		x += step_x;
		y += step_y;
	}
}

int	deal_key(int key, void *param)
{
	printf("key: %d\n", key);
	return (0);
}

void	draw(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, 1000, 1000, "FDF");
	
	bresenham(10, 10, 600, 300, fdf);
	mlx_key_hook(fdf->window, deal_key, NULL);
	mlx_loop(fdf->mlx);
	
	
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac != 2)
		return (write(1, "Error: Invalid number of arguments\n", 35));
	fdf = (t_fdf){.map = &(t_map){.coordinates = &(t_point *){0}}};
	ft_initialization(&fdf, av[1]);
	print_map(&fdf);
	print_colors(&fdf);
	if (!fdf.error_message)
		draw(&fdf);
	else
		printf("error_message: %s\n", fdf.error_message);
	return (0);
}

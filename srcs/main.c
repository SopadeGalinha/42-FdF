/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:18:23 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/12 17:50:48 by jhoonca          ###   ########.fr       */
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

void	ft_render(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_NAME);
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
		ft_render(&fdf);
	else
		printf("error_message: %s\n", fdf.error_message);
	return (0);
}

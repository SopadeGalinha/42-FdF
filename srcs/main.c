/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:18:23 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/17 22:01:45 by jhoonca          ###   ########.fr       */
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
	printf("key: %d\n", key);
	return (0);
}

void apply_isometric(float *x, float *y, int z, int zoom)
{
    *x = (*x - *y) * cos(0.523599);
    *y = (*x + *y) * sin(0.523599) - z * zoom;
}

void bresenham(float x_iso, float y_iso, float x1_iso, float y1_iso, t_fdf *fdf, int color)
{
    float x_step;
    float y_step;
    int max;

    x_step = x1_iso - x_iso;
    y_step = y1_iso - y_iso;

    max = MAX(mod(x_step), mod(y_step));
    x_step /= max;
    y_step /= max;

    while ((int)(x_iso - x1_iso) || (int)(y_iso - y1_iso))
    {
        mlx_pixel_put(fdf->mlx, fdf->window, x_iso, y_iso, color);
        x_iso += x_step;
        y_iso += y_step;
    }
}

void render(t_fdf *fdf)
{
    int y;
    int x;

    fdf->window = mlx_new_window(fdf->mlx, fdf->window_width, fdf->window_height, WINDOW_NAME);
    fdf->map->zoom = 20;
    int center_x = fdf->window_width / 2;
    int center_y = fdf->window_height / 2;

    // Calculate the center pixel of the map
    int center_pixel_x = fdf->map->max_x * fdf->map->zoom / 2;
    int center_pixel_y = fdf->map->max_y * fdf->map->zoom / 2;

    // Calculate the displacement needed to center the map
    int x_displacement = center_x - center_pixel_x;
    int y_displacement = center_y - center_pixel_y;

    y = -1;
    while (++y < fdf->map->max_y)
    {
        x = -1;
        while (++x < fdf->map->max_x)
        {
            float x_iso = x * fdf->map->zoom;
            float y_iso = y * fdf->map->zoom;
            float z_iso = fdf->map->coordinates[y][x].z * fdf->map->zoom;

            // Apply isometric transformation
            apply_isometric(&x_iso, &y_iso, z_iso, fdf->map->zoom);

            // Apply the displacement to center the map
            x_iso += x_displacement;
            y_iso += y_displacement;

            if (x < fdf->map->max_x - 1)
            {
                float x1_iso = (x + 1) * fdf->map->zoom;
                float y1_iso = y * fdf->map->zoom;
                float z1_iso = fdf->map->coordinates[y][x + 1].z * fdf->map->zoom;

                apply_isometric(&x1_iso, &y1_iso, z1_iso, fdf->map->zoom);

                x1_iso += x_displacement;
                y1_iso += y_displacement;

                bresenham(x_iso, y_iso, x1_iso, y1_iso, fdf, fdf->map->coordinates[y][x].color);
            }

            if (y < fdf->map->max_y - 1)
            {
                float x1_iso = x * fdf->map->zoom;
                float y1_iso = (y + 1) * fdf->map->zoom;
                float z1_iso = fdf->map->coordinates[y + 1][x].z * fdf->map->zoom;

                apply_isometric(&x1_iso, &y1_iso, z1_iso, fdf->map->zoom);

                x1_iso += x_displacement;
                y1_iso += y_displacement;

                bresenham(x_iso, y_iso, x1_iso, y1_iso, fdf, fdf->map->coordinates[y][x].color);
            }
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
		render(&fdf);
	else
		printf("error_message: %s\n", fdf.error_message);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:47:02 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/18 18:17:10 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Interpolate between two RGB colors
// Extract the red, green, and blue components of color1
// Extract the red, green, and blue components of color2
// Interpolate each color component separately

// Interpolate red
// Interpolate green
// Interpolate blue

// Combine the interpolated components to form the final color
int	interpolate_color(int color1, int color2, float progress)
{
	int	rgb[9];

	rgb[R1] = (color1 >> 16) & 0xFF;
	rgb[G1] = (color1 >> 8) & 0xFF;
	rgb[B1] = color1 & 0xFF;
	rgb[R2] = (color2 >> 16) & 0xFF;
	rgb[G2] = (color2 >> 8) & 0xFF;
	rgb[B2] = color2 & 0xFF;
	rgb[R] = rgb[R1] + (int)((rgb[R2] - rgb[R1]) * progress);
	rgb[G] = rgb[G1] + (int)((rgb[G2] - rgb[G1]) * progress);
	rgb[B] = rgb[B1] + (int)((rgb[B2] - rgb[B1]) * progress);
	return ((rgb[R] << 16) | (rgb[G] << 8) | rgb[B]);
}

static void	isometric_projection(t_fdf fdf, t_points *points_to_draw)
{
	while (fdf.coords->x != INT_MIN)
	{
		points_to_draw->x = fdf.coords->x * fdf.zoom + fdf.offset.x;
		points_to_draw->y = -fdf.coords->z * fdf.zoom + fdf.offset.y;
		fdf.coords++;
		points_to_draw++;
	}
	points_to_draw->x = INT_MIN;
}

void	render(t_fdf *fdf)
{
	void		*image;
	t_image		data;
	t_points	*points_to_draw;

	data.endian = 0;
	image = mlx_new_image(fdf->mlx, fdf->window_width, fdf->window_height);
	data.buffer = mlx_get_data_addr(image, &data.bits_per_pixel, \
		&data.size_line, &data.endian);
	points_to_draw = malloc(sizeof(t_points) * \
		(fdf->map_size.x * fdf->map_size.y + 1));
	isometric_projection(*fdf, points_to_draw);
	draw_map(fdf, points_to_draw, &data);
	mlx_put_image_to_window(fdf->mlx, fdf->win, image, 0, 0);
	mlx_destroy_image(fdf->mlx, image);
	free(points_to_draw);
}

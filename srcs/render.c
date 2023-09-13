/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:47:02 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/13 19:43:10 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
	t_points	*points_to_draw;
	void		*image;
	t_image		data;

	data.endian = 0;
	image = mlx_new_image(fdf->mlx, fdf->window_width, fdf->window_height);
	data.buffer = mlx_get_data_addr(image, &data.bits_per_pixel, &data.size_line, &data.endian);
	points_to_draw = malloc(sizeof(t_points) * \
		(fdf->map_size.x * fdf->map_size.y + 1));
	isometric_projection(*fdf, points_to_draw);
	draw_map(fdf, points_to_draw, &data);
	mlx_put_image_to_window(fdf->mlx, fdf->win, image, 0, 0);
	mlx_destroy_image(fdf->mlx, image);
	free(points_to_draw);
}

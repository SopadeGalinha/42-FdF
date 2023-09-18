/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_graphics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:46:13 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/17 05:34:49 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	set_zoom(t_fdf *fdf)
{
	float	zoom;
	float	sizes[3];

	sizes[X] = fdf->window_width * 0.5f / fdf->limits.max_x;
	sizes[Y] = fdf->window_height * 0.5f / fdf->limits.max_y;
	if (fabsf(fdf->limits.min_z) > fdf->limits.max_z)
		sizes[2] = fdf->window_height * 0.5f / \
			fabsf(fdf->limits.min_z) * 0.8f;
	else
		sizes[2] = fdf->window_height * 0.5f / fdf->limits.max_z * 0.8f;
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
	fdf->mlx = mlx_init();
	mlx_get_screen_size(fdf->mlx, &(fdf->window_width), &(fdf->window_height));
	fdf->window_width = fdf->window_width / 2;
	fdf->window_height = fdf->window_width / 2;
	fdf->offset = (t_points){(fdf->window_width / 2), (fdf->window_width / 3)};
	fdf->colors = fdf->original_colors;
	fdf->win = mlx_new_window(fdf->mlx, fdf->window_width, \
		fdf->window_height, "FdF");
	set_zoom(fdf);
}

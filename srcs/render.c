/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:47:02 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/11 19:45:06 by jhoonca          ###   ########.fr       */
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

	points_to_draw = malloc(sizeof(t_points) * \
		(fdf->map_size.x * fdf->map_size.y + 1));
	isometric_projection(*fdf, points_to_draw);
	draw_map(fdf, points_to_draw);
	free(points_to_draw);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:44:50 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/18 18:15:39 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	bresenham(t_draw *line, int *state)
{
	state[ERR2] = 2 * state[ERR];
	if (state[ERR2] > -state[DELTA_Y])
	{
		state[ERR] -= state[DELTA_Y];
		line->p0.x += state[STEP_X];
	}
	if (state[ERR2] < state[DELTA_X])
	{
		state[ERR] += state[DELTA_X];
		line->p0.y += state[STEP_Y];
	}
}

static void	init_bresenham(t_draw line, int *state)
{
	state[DELTA_X] = abs(line.p1.x - line.p0.x);
	state[DELTA_Y] = abs(line.p1.y - line.p0.y);
	if (line.p0.x < line.p1.x)
		state[STEP_X] = 1;
	else
		state[STEP_X] = -1;
	if (line.p0.y < line.p1.y)
		state[STEP_Y] = 1;
	else
		state[STEP_Y] = -1;
	state[ERR] = state[DELTA_X] - state[DELTA_Y];
}

void	ft_pixel_put(t_fdf *fdf, int *xy, int color, t_image *data)
{
	int	pixel;

	if (xy[X] < 0 || xy[X] >= fdf->window_width
		|| xy[Y] < 0 || xy[Y] >= fdf->window_height)
		return ;
	pixel = (xy[Y] * data->size_line) + (xy[X] * 4);
	if (data->endian)
	{
		data->buffer[pixel + 0] = (color >> 24);
		data->buffer[pixel + 1] = (color >> 16) & 0xFF;
		data->buffer[pixel + 2] = (color >> 8) & 0xFF;
		data->buffer[pixel + 3] = (color) & 0xFF;
	}
	else if (!data->endian)
	{
		data->buffer[pixel + 0] = (color) & 0xFF;
		data->buffer[pixel + 1] = (color >> 8) & 0xFF;
		data->buffer[pixel + 2] = (color >> 16) & 0xFF;
		data->buffer[pixel + 3] = (color >> 24);
	}
}

// Function to draw a line using Bresenham's algorithm with color interpolation
static void	draw_line(t_fdf *fdf, t_draw line, int *colors, t_image *data)
{
	int		color;
	float	interpolate;
	int		state[7];
	int		xy[2];

	interpolate = 0.0;
	init_bresenham(line, state);
	while (line.p0.x != line.p1.x || line.p0.y != line.p1.y)
	{
		color = interpolate_color(colors[0], colors[1], interpolate);
		xy[X] = line.p0.x;
		xy[Y] = line.p0.y;
		ft_pixel_put(fdf, xy, color, data);
		bresenham(&line, state);
		interpolate += 1.0 / (sqrt(state[DELTA_X] * state[DELTA_X] \
			+ state[DELTA_Y] * state[DELTA_Y]) + 1);
	}
	color = interpolate_color(colors[0], colors[1], interpolate);
	ft_pixel_put(fdf, xy, color, data);
}

void	draw_map(t_fdf *fdf, t_points *pts, t_image *data)
{
	int		i;
	t_draw	line_to_draw;
	int		colors[2];

	i = -1;
	while (pts[++i].x != INT_MIN)
	{
		if (i % fdf->map_size.x != fdf->map_size.x - 1)
		{
			line_to_draw.p0 = (t_points){pts[i].x, pts[i].y};
			line_to_draw.p1 = (t_points){pts[i + 1].x, pts[i + 1].y};
			colors[0] = fdf->colors[i];
			colors[1] = fdf->colors[i + 1];
			draw_line(fdf, line_to_draw, colors, data);
		}
		if (i + fdf->map_size.x < fdf->map_size.x * fdf->map_size.y)
		{
			line_to_draw.p0 = (t_points){pts[i].x, pts[i].y};
			line_to_draw.p1 = (t_points){pts[i + \
				fdf->map_size.x].x, pts[i + fdf->map_size.x].y};
			colors[0] = fdf->colors[i];
			colors[1] = fdf->colors[i + fdf->map_size.x];
			draw_line(fdf, line_to_draw, colors, data);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:44:50 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/11 19:45:47 by jhoonca          ###   ########.fr       */
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
static int	interpolate_color(int color1, int color2, float progress)
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

// Move right
// Move left
// Move down
// Move up
// Initialize the error term
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

// Function to draw a line using Bresenham's algorithm with color interpolation
static void	draw_line(t_fdf *fdf, t_draw line, int c1, int c2)
{
	int		color;
	float	interpolate;
	int		state[7];

	interpolate = 0.0;
	init_bresenham(line, state);
	while (line.p0.x != line.p1.x || line.p0.y != line.p1.y)
	{
		color = interpolate_color(c1, c2, interpolate);
		mlx_pixel_put(fdf->mlx, fdf->win, line.p0.x, line.p0.y, color);
		bresenham(&line, state);
		interpolate += 1.0 / (sqrt(state[DELTA_X] * state[DELTA_X] \
			+ state[DELTA_Y] * state[DELTA_Y]) + 1);
	}
	color = interpolate_color(c1, c2, interpolate);
	mlx_pixel_put(fdf->mlx, fdf->win, line.p0.x, line.p0.y, color);
}

void	draw_map(t_fdf *fdf, t_points *pts)
{
	int		i;
	t_draw	line_to_draw;

	i = -1;
	while (pts[++i].x != INT_MIN)
	{
		if (i % fdf->map_size.x != fdf->map_size.x - 1)
		{
			line_to_draw.p0 = (t_points){pts[i].x, pts[i].y};
			line_to_draw.p1 = (t_points){pts[i + 1].x, pts[i + 1].y};
			draw_line(fdf, line_to_draw, fdf->colors[i], fdf->colors[i + 1]);
		}
		if (i + fdf->map_size.x < fdf->map_size.x * fdf->map_size.y)
		{
			line_to_draw.p0 = (t_points){pts[i].x, pts[i].y};
			line_to_draw.p1 = (t_points){pts[i + \
				fdf->map_size.x].x, pts[i + fdf->map_size.x].y};
			draw_line(fdf, line_to_draw, fdf->colors[i],
				fdf->colors[i + fdf->map_size.x]);
		}
	}
}

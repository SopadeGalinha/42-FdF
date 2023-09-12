/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:57:38 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/12 21:32:13 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_coords	rotate(t_coords point, float angle, int axis)
{
	float	angle_rad;
	float	cos_theta;
	float	sin_theta;
	float	temp[3];

	angle_rad = angle * (PI / 180.0);
	cos_theta = cosf(angle_rad);
	sin_theta = sinf(angle_rad);
	if (axis == AXIS_X)
	{
		temp[Y] = point.y;
		temp[Z] = point.z;
		point.y = temp[Y] * cos_theta - temp[Z] * sin_theta;
		point.z = temp[Y] * sin_theta + temp[Z] * cos_theta;
	}
	if (axis == AXIS_Z)
	{
		temp[X] = point.x;
		temp[Y] = point.y;
		point.x = temp[X] * cos_theta - temp[Y] * sin_theta;
		point.y = temp[X] * sin_theta + temp[Y] * cos_theta;
	}
	return (point);
}

static void	apply_rotation(t_coords *coords, t_points direction)
{
	float	angle[2];

	angle[X] = direction.x;
	angle[Y] = direction.y;
	while (coords->x != INT_MIN)
	{
		*coords = rotate(*coords, angle[X], AXIS_Z);
		*coords = rotate(*coords, -angle[Y], AXIS_X);
		coords++;
	}
}

static void	center_map(t_coords *points, t_points map_size)
{
	while (points->x != INT_MIN)
	{
		points->x -= ((float)map_size.x / 2 - 0.5f);
		points->y -= ((float)map_size.y / 2 - 0.5f);
		points++;
	}
}

static void	set_limits(t_coords *coords, t_limits *limits)
{
	limits->min_x = (float)INT_MAX;
	limits->max_x = (float)INT_MIN;
	limits->min_y = (float)INT_MAX;
	limits->max_y = (float)INT_MIN;
	limits->min_z = (float)INT_MAX;
	limits->max_z = (float)INT_MIN;
	while (coords->x != INT_MIN)
	{
		if (coords->x < limits->min_x)
			limits->min_x = coords->x;
		if (coords->x > limits->max_x)
			limits->max_x = coords->x;
		if (coords->y < limits->min_y)
			limits->min_y = coords->y;
		if (coords->y > limits->max_y)
			limits->max_y = coords->y;
		if (coords->z < limits->min_z)
			limits->min_z = coords->z;
		if (coords->z > limits->max_z)
			limits->max_z = coords->z;
		coords++;
	}
}

void	set_display(t_fdf *fdf)
{
	center_map(fdf->coords, fdf->map_size);
	apply_rotation(fdf->coords, (t_points){40, 33});
	set_limits(fdf->coords, &fdf->limits);
}

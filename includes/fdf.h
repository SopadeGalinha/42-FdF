/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 23:30:29 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/10 00:02:12 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include <X11/Xlib.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

# define PI 3.14159265358979323846

# define ERROR_MAP		"Found wrong line length. Exiting.\n"
# define ERROR_EXT		"ERROR file extension. Exiting.\n"
# define ERROR_INPUT	"ERROR input. Exiting.\n"
# define ERROR_MALLOC	"malloc error. Exiting.\n"
# define ERROR_OPEN		"open error\n"
# define ERROR_EMP_FD	"empty file\n"

enum e_rotation
{
	AXIS_X,
	AXIS_Z
};

enum e_position
{
	X,
	Y,
	Z
};

typedef struct s_points {
	int	x;
	int	y;
}				t_points;

typedef struct s_coords {
	float	x;
	float	y;
	float	z;
	int		color;
}				t_coords;

typedef struct s_draw {
	t_points	p0;
	t_points	p1;
}				t_draw;

typedef struct s_bresenham {
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	x;
	int	y;
	int	e2;
}				t_bresenham;

typedef struct s_limits {
	float	min_x;
	float	max_x;

	float	min_y;
	float	max_y;

	float	min_z;
	float	max_z;
}				t_limits;

typedef struct s_fdf {
	void		*mlx;
	t_points	offset;
	void		*win;
	float		zoom;
	t_coords	*coords;
	int			*colors;
	int			*color;
	int			*height_colors;
	t_points	map_size;
	t_limits	limits;
	int			window_width;
	int			window_height;
}				t_fdf;

# ifndef WINX
#  define WINX 1200
# endif
# ifndef WINY
#  define WINY 700
# endif

void ft_free_array(char **split_ptr);
int			list_length(char **list);
int			points_in_line(char	*line);
int			ft_strpos(char *str, char c);
int	ft_atoi_base(const char *nptr, const char *base);
void	set_graphics(t_fdf *fdf);

void    set_display(t_fdf *fdf);

void		set_limits(t_coords *points, t_limits *object_limits);
void		initialize_zoom(t_fdf *fdf);
void		adjust_pivot(t_coords *points, t_points map_size);
void		create_height_colors(t_fdf fdf);
char		*init(char *map, t_fdf *fdf);

int			interpolate_color(int color1, int color2, float t);

void		apply_rotation(t_coords *points3d, t_points direction);
void		switch_projection(t_fdf *fdf);
void		switch_colors(t_fdf *fdf);
void		close_app(t_fdf *fdf);
size_t	ft_count_char(char *str, char c);
bool	ft_contains(const char *haystack, const char *needle);

void		draw_line(t_fdf *fdf, t_draw line, int c1, int c2);
void		 render(t_fdf *fdf);

#endif
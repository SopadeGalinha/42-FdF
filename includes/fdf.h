/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 23:30:29 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/13 21:16:30 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// INCLUDES

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include "./minilibx/mlx.h"
# include "./libft/libft.h"

/*____________________________________________________________________________*/

// MACROS

# define PI				3.14159265358979323846
# define DBASE			"0123456789"
# define HBASE			"0123456789abcdef"
# define ERROR_OPEN		"Error: open\n"
# define ERROR_EMP_FD	"Error: Empty file\n"
# define ERROR_INPUT	"Error: input. Exiting.\n"
# define ERROR_MALLOC	"Error: malloc. Exiting.\n"
# define ERROR_EXT		"Error: file extension. Exiting.\n"
# define ERROR_MAP		"Error: Found wrong line length. Exiting.\n"

/*____________________________________________________________________________*/

//Structs
typedef struct s_points {
	int	x;
	int	y;
}				t_points;

typedef struct s_coords {
	float	x;
	float	y;
	float	z;
}				t_coords;

typedef struct s_draw {
	t_points	p0;
	t_points	p1;
}				t_draw;

typedef struct s_limits{
	float	min_x;
	float	max_x;
	float	min_y;
	float	max_y;
	float	min_z;
	float	max_z;
}				t_limits;

typedef struct s_image {
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*buffer;
}	t_image;
typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	float		zoom;
	int			*original_colors;
	int			*colors;
	int			window_width;
	int			window_height;
	int			*height_colors;
	t_limits	limits;
	t_points	offset;
	t_points	map_size;
	t_coords	*coords;
	t_image		*data;
}				t_fdf;

//Enums
enum e_state
{
	AXIS_X,
	AXIS_Z,
	X = 0,
	Y,
	Z,
	DELTA_X = 2,
	DELTA_Y,
	STEP_X,
	STEP_Y,
	ERR,
	ERR2,
	R = 0,
	G,
	B,
	R1,
	G1,
	B1,
	R2,
	G2,
	B2,
};
		
enum keycodes
{
	LEFT_A = 0x61,
	DOWN_S = 0x73,
	RIGHT_D = 0x64,
	UP_W = 0x77,
	ESC = 0xFF1B,
	LEFT_ARROW = 0xff51,
	DOWN_ARROW = 0xff54,
	RIGHT_ARROW = 0xff53,
	UP_ARROW = 0xff52,
	ON_PRESS = 1L<<15,
	ON_RELEASE = 1L<<1,
};

//Prototypes
char	*init(char *map, t_fdf *fdf);
void	set_display(t_fdf *fdf);
void	set_graphics(t_fdf *fdf);
void	render(t_fdf *fdf);
void	draw_map(t_fdf *fdf, t_points *pts, t_image *data);

void	ft_free_array(char **split_ptr);
size_t	ft_count_char(char *str, char c);
int		ft_atoi_base(const char *nptr, const char *base);
bool	ft_contains(const char *haystack, const char *needle);

int	keycode(int keycode, t_fdf *fdf);
int	mousecode(int button, int x, int y, t_fdf *fdf);


#endif
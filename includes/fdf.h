/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 00:31:27 by jhogonca          #+#    #+#             */
/*   Updated: 2023/09/06 18:43:27 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include <pthread.h>
# include <math.h>
# include <limits.h>

# define WINDOW_NAME	"42 - FDF - SopadeGalinha"

#define WINDOW_FULL_SCREEN	0

#define MAX(a, b) (a > b ? a : b);

#define MIN(a, b) (a < b ? a : b);
#define MOD(a) (a < 0 ? -a : a);

enum e_axis
{
	START_X,
	END_X,
	START_Y,
	END_Y,
	START_Z,
	END_Z,
};

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;	
}		t_point;

typedef struct s_center
{
	int	center_x;
	int	center_y;
	int	screen_center_x;
	int	screen_center_y;
}		t_center;

typedef struct s_map
{
	t_point	**coordinates;
	int			max_x;
	int			max_y;
	int			max_z;
	int			min_z;
	int			zoom;
}	t_map;

typedef struct s_fdf
{
	t_map	*map;
	void	*window;
	void	*mlx;
	int		window_width;
	int		window_height;
	char	*error_message;
	t_center	*center;
}		t_fdf;

/*____________________FUCTIONS____________________*/

void	ft_initialization(t_fdf *fdf, char *map);
int		ft_atoi_base(const char *str, int base);
void	get_dimensions(t_fdf *fdf, int fd);
void	ft_free_split(char **split);

#endif

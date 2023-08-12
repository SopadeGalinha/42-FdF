/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 00:31:27 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/12 17:49:26 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include <pthread.h>
# include <math.h>

# define WINDOW_NAME	 	"fdf"
# define WINDOW_WIDTH		1200
# define WINDOW_HEIGHT		900

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}		t_point;
typedef struct s_map
{
	t_point	**coordinates;
	int		max_x;
	int		max_y;
	int		max_z;
	int		min_z;
}	t_map;

typedef struct s_fdf
{
	t_map	*map;
	void	*window;
	void	*mlx;
	char	*error_message;
}		t_fdf;

/*____________________FUCTIONS____________________*/

void	ft_initialization(t_fdf *fdf, char *map);
int		ft_atoi_base(const char *str, int base);
void	get_dimensions(t_fdf *fdf, int fd);
void	ft_free_split(char **split);

#endif

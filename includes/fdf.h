/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 00:31:27 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/09 19:02:07 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include <pthread.h>
# include <math.h>

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int	color;
}		t_point;

typedef struct s_map
{
	t_point **coordinates;
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

#endif

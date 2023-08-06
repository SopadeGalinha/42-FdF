/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 00:31:27 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/07 00:03:06 by jhogonca         ###   ########.fr       */
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

typedef struct s_fdf
{
	void	*window;
	void	*mlx;
	int		max_x;
	int		max_y;
	bool	error;
	char	*error_message;
	t_point	coordinates;
}		t_fdf;

#endif

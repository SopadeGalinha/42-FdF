/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 00:31:27 by jhogonca          #+#    #+#             */
/*   Updated: 2023/07/26 20:50:01 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif

# include "./minilibx/mlx.h"
# include "./libft/libft.h"

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
	bool	error;
	t_point	**coordinates;
}		t_fdf;

#endif

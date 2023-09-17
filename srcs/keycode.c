/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:59:24 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/17 03:54:53 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	moves_wasd(t_fdf *fdf, int keycode)
{
	int	i;

	i = -1;
	if (keycode == LEFT_A || keycode == LEFT_ARROW)
		while (fdf->coords[++i].x != INT_MIN)
			fdf->coords[i].x -= 5;
	if (keycode == RIGHT_D || keycode == RIGHT_ARROW)
		while (fdf->coords[++i].x != INT_MIN)
			fdf->coords[i].x += 5;
	if (keycode == UP_ARROW || keycode == UP_W)
		while (fdf->coords[++i].x != INT_MIN)
			fdf->coords[i].z += 5;
	if (keycode == DOWN_ARROW || keycode == DOWN_S)
		while (fdf->coords[++i].x != INT_MIN)
			fdf->coords[i].z -= 5;
	render(fdf);
}

int	keycode(int keycode, t_fdf *fdf)
{
	if (keycode == 0xFF1B)
		mlx_loop_end(fdf->mlx);
	if ((keycode == 0x61 || keycode == 0xff51)
		|| (keycode == 0x73 || keycode == 0xff54)
		|| (keycode == 0x64 || keycode == 0xff53)
		|| (keycode == 0x77 || keycode == 0xff52))
		moves_wasd(fdf, keycode);
	return (0);
}

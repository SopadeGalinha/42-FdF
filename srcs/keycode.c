/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:59:24 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/12 22:09:51 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	moves_wasd(t_fdf *fdf, int keycode)
{
	int	i;

	i = -1;
	if (keycode == LEFT_A || keycode == LEFT_ARROW)
		while (fdf->coords[++i].x != INT_MIN)
			fdf->coords[i].x -= 3;
	if (keycode == RIGHT_D || keycode == RIGHT_ARROW)
		while (fdf->coords[++i].x != INT_MIN)
			fdf->coords[i].x += 3;
	if (keycode == UP_ARROW || keycode == UP_W)
		while (fdf->coords[++i].x != INT_MIN)
			fdf->coords[i].z += 3;
	if (keycode == DOWN_ARROW || keycode == DOWN_S)
		while (fdf->coords[++i].x != INT_MIN)
			fdf->coords[i].z -= 3;
	mlx_clear_window(fdf->mlx, fdf->win);
	render(fdf);
}

int	keycode(int keycode, t_fdf *fdf)
{
	if (keycode == 0xFF1B)
		mlx_loop_end(fdf->mlx);
	printf("keycode: %x\n", keycode);
	if ((keycode == 0x61 || keycode == 0xff51) // a or left arrow (left)
		|| (keycode == 0x73 || keycode == 0xff54) // s or down arrow (down)
		|| (keycode == 0x64 || keycode == 0xff53) // d or right arrow (right)
		|| (keycode == 0x77 || keycode == 0xff52)) // w or up arrow (up)
		moves_wasd(fdf, keycode);
	return (0);
}

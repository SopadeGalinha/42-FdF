/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:24:32 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/11 23:46:12 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_clean(t_fdf *fdf, char *error)
{
	if (fdf->coords)
		free(fdf->coords);
	if (fdf->colors)
		free(fdf->colors);
	if (fdf->height_colors)
		free(fdf->height_colors);
	if (fdf->mlx)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
		mlx_destroy_display(fdf->mlx);
	if (fdf->mlx)
		free(fdf->mlx);
	if (error != NULL)
		ft_printf("\x1B[31;1m%s\x1B[0m", error);
	else
		ft_printf("\x1B[32;1m%s\x1B[0m", "Bye Bye!");
}

int	keycode(int keycode, t_fdf *fdf)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 0xFF1B)
		mlx_loop_end(fdf->mlx);
	if (keycode == 0x63)
	{
		// fdf->colors = fdf->colors == fdf->original_colors
			// ? fdf->height_colors : fdf->original_colors;
		// refresh_image(fdf);
	}
	return (0);
}

int	mousecode(int button, int x, int y, t_fdf *fdf)
{
	if (fdf->coords->x == INT_MIN)
		return (0);
	printf("button: %d\n", button);
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	return (0);
}

void	set_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, keycode, fdf);
	mlx_mouse_hook(fdf->win, mousecode, fdf);
	mlx_hook(fdf->win, 17, 1L << 15, mlx_loop_end, fdf->mlx);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;
	char	*error;

	fdf = (t_fdf){0};
	if (ac != 2)
		error = ERROR_INPUT;
	else
		error = init(av[1], &fdf);
	if (!error)
	{
		set_display(&fdf);
		set_graphics(&fdf);
		render(&fdf);
		set_hooks(&fdf);
	}
	if (!error)
		mlx_loop(fdf.mlx);
	ft_clean(&fdf, error);
	return (0);
}

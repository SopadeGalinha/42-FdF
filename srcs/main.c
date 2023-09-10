/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:24:32 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/10 22:09:47 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_clean(t_fdf *fdf, char *error)
{
	if (fdf->coords != NULL) 
	{
		free(fdf->coords);
		fdf->coords = NULL;
	}
	if (fdf->colors != NULL) 
	{
		free(fdf->colors);
		fdf->colors = NULL;
	}
	if (fdf->height_colors != NULL) 
	{
		free(fdf->height_colors);
		fdf->height_colors = NULL;
	}
	if (fdf->win != 0)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx != NULL)
		mlx_destroy_display(fdf->mlx);
	if (fdf->mlx != NULL)
		free(fdf->mlx);
	if (error != NULL)
		ft_printf("\x1B[31;1m%s\x1B[0m", error);
}

int	keycode(int keycode, t_fdf *fdf)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 0xFF1B)
		mlx_loop_end(fdf->mlx);
	return (0);
}

int	mousecode(int button, int x, int y, t_fdf *fdf)
{
	printf("button: %d\n", button);
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	return (0);
}

void	set_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, keycode, fdf);
	mlx_mouse_hook(fdf->win, mousecode, fdf);
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

/* *************************************************************************** */
/*                                                                             */
/*                                                         :::      ::::::::   */
/*   new.c                                               :+:      :+:    :+:   */
/*                                                     +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>      +#+  +:+       +#+        */
/*                                                 +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:33:27 by jhogonca           #+#    #+#             */
/*   Updated: 2023/09/09 17:33:28 by jhogonca          ###   ########.fr       */
/*                                                                             */
/* *************************************************************************** */

#include "../includes/fdf.h"

int main(int ac, char **av)
{
	t_fdf fdf;
	char *error;

	if (ac != 2)
		return (write(1, ERROR_INPUT, ft_strlen(ERROR_INPUT)));
	fdf = (t_fdf){0};
	error = init(av[1], &fdf);
	if (error)
		return (write(1, error, ft_strlen(error)));
	set_display(&fdf);
	set_graphics(&fdf);
	render(&fdf);
//	set_hooks(fdf);
	mlx_loop(fdf.mlx);
	return (0);
}

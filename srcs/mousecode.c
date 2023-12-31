/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousecode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:59:00 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/22 18:12:29 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	mousecode(int button, int x, int y, t_fdf *fdf)
{
	if (fdf->coords->x == INT_MIN)
		return (0);
	if (x + y == 0)
		return (0);
	if (button < 0)
		return (0);
	return (1);
}

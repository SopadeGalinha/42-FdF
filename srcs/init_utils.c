/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:59:13 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/11 16:59:13 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	ft_arrlen(char **arr);
void		ft_free_split(char **split);

void	get_dimensions(t_fdf *fdf, int fd)
{
	char	*line;
	char	**split;

	line = get_next_line(fd);
	while (line)
	{
		fdf->map->max_y++;
		split = ft_split(line, ' ');
		if (fdf->map->max_x == 0)
			fdf->map->max_x = ft_arrlen(split);
		else if (fdf->map->max_x != ft_arrlen(split))
			fdf->error_message = "Error: Invalid map 1\n";
		free(line);
		ft_free_split(split);
		if (fdf->error_message)
			return ;
		line = get_next_line(fd);
	}
	if ((fdf->map->max_y < 2 || fdf->map->max_x < 2)
		|| (fdf->map->max_y > 1000 || fdf->map->max_x > 1000))
			fdf->error_message = "Error: Invalid map 2\n";
}

void	ft_free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

static int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] && arr[i][0] != '\n')
		i++;
	return (i);
}

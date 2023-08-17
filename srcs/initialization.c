/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 00:44:11 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/17 20:26:29 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	set_map_aux(int j, t_fdf *fdf, char **split, int i)
{
	while (j < fdf->map->max_x)
	{
		fdf->map->coordinates[i][j].x = j;
		fdf->map->coordinates[i][j].y = i;
		fdf->map->coordinates[i][j].z = ft_atoi_base(split[j], 10);
		if (ft_strstr(split[j], ","))
		{
			fdf->map->coordinates[i][j].color
				= ft_atoi_base(ft_strnstr(split[j], "0x", 8), 16);
			if (fdf->map->coordinates[i][j].color == 0)
				fdf->map->coordinates[i][j].color = 0xFFFFFF;
		}
		else
			fdf->map->coordinates[i][j].color = 0xFFFFFF;
		j++;
	}
}

static void	set_map( t_fdf *fdf, char *map)
{
	int		fd;
	char	*line;
	char	**split;
	int		i;
	int		j;

	fd = open(map, O_RDONLY);
	fdf->map->coordinates \
		= (t_point **)malloc(sizeof(t_point *) * fdf->map->max_y);
	i = 0;
	while (i < fdf->map->max_y)
	{
		fdf->map->coordinates[i]
			= (t_point *)malloc(sizeof(t_point) * fdf->map->max_x);
		j = 0;
		line = get_next_line(fd);
		split = ft_split(line, ' ');
		set_map_aux(j, fdf, split, i);
		ft_free_split(split);
		free(line);
		i++;
	}
	close(fd);
}

static bool valid_path(char *map, t_fdf *fdf)
{
	int	c;
	int i;

	c = 0;
	i = -1;
	if (!(ft_strstr(map, ".fdf")) || ft_strlen(map) < 5)
		fdf->error_message = "Error: Invalid file extension\n";
	while (map[++i])
		if (map[i] == '.')
			c++;	
	if (c != 1)
		fdf->error_message = "Error: Invalid file extension\n";
	if (fdf->error_message)
		return (false);
	return (true);
}

void	ft_initialization(t_fdf *fdf, char *map)
{
	int	fd;

	if (!valid_path(map, fdf))
		return ;
	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		fdf->error_message = "Error: open() failed\n";
		return ;
	}
	get_dimensions(fdf, fd);
	if (!fdf->error_message)
		set_map(fdf, map);
	if (!fdf->error_message)
	{
		fdf->mlx = mlx_init();
		mlx_get_screen_size(fdf->mlx, &(fdf->window_width), &(fdf->window_height));
	 	fdf->window_width = fdf->window_width / 1.5;
		fdf->window_height = fdf->window_width / 1.5;
 	}
	close(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:18:23 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/09 20:20:18 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fdf.h"

void	ft_free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] && arr[i][0] != '\n')
		i++;
	return (i);
}

static void get_dimensions(t_fdf *fdf, int fd)
{
	char *line;
	char **split;

	line = get_next_line(fd);
	while (line)
	{
		fdf->map->max_y++;
		split = ft_split(line, ' ');
		if (fdf->map->max_x == 0)
			fdf->map->max_x = ft_arrlen(split);
		else if (fdf->map->max_x != ft_arrlen(split))
			fdf->error_message = "Error: Invalid map 1\n";
		ft_free_split(split);
		free(line);
		if (fdf->error_message)
			return ;
		line = get_next_line(fd);
	}
	if ((fdf->map->max_y < 2 || fdf->map->max_x < 2)
		|| (fdf->map->max_y > 1000 || fdf->map->max_x > 1000))
			fdf->error_message = "Error: Invalid map 2\n";
}

void	set_map( t_fdf *fdf)
{
	int i;

	i = 0;
	fdf->map->coordinates = (t_point **)malloc(sizeof(t_point *) * fdf->map->max_y);
	if (!fdf->map)
	{
		fdf->error_message = "Error: malloc() failed\n";
		return;
	}
	while (i < fdf->map->max_y)
	{
		fdf->map->coordinates[i] = (t_point *)malloc(sizeof(t_point) * fdf->map->max_x);
		if (!fdf->map->coordinates[i])
		{
			fdf->error_message = "Error: malloc() failed\n";
			return;
		}
		i++;
	}
}

void ft_initialization(t_fdf *fdf, char *map)
{
	int fd;

	if (!(ft_strstr(map, ".fdf")) || ft_strlen(map) < 5)
	{
		fdf->error_message = "Error: Invalid file extension\n";
		return;
	}

	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		fdf->error_message = "Error: open() failed\n";
		return;
	}
	get_dimensions(fdf, fd);
	// if (!fdf->error_message)
		// set_map(fdf);
	close(fd);
}



int main(int ac, char **av)
{
	t_fdf	fdf;
	if (ac != 2)
		return (write(1, "Error: Invalid number of arguments\n", 35));
	fdf = (t_fdf) {0};
	fdf.map = &((t_map){0});
	fdf.map->coordinates = &((t_point*){0});
	ft_initialization(&fdf, av[1]);
	
	printf("error_message: %s\n", fdf.error_message);
	printf("x: %d\n", fdf.map->max_x);
	printf("y: %d\n", fdf.map->max_y);
	return (0);
}
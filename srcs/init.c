/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:00:48 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/12 20:34:50 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static char			*get_coords(char *fdf_path, t_points *map_size);
static unsigned int	get_color(char *str);

static void	set_map(t_fdf *fdf, int fd)
{
	int			xy[2];
	char		*line;
	int			*clrs;
	char		**split;
	t_coords	*ps;

	xy[Y] = -1;
	ps = fdf->coords;
	clrs = fdf->original_colors;
	while (++xy[Y] < fdf->map_size.y)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split = ft_split(line, ' ');
		xy[X] = -1;
		while (++xy[X] < fdf->map_size.x)
		{
			*ps++ = (t_coords){xy[X], xy[Y], ft_atoi_base(split[xy[X]], DBASE)};
			*clrs++ = get_color(split[xy[X]]);
		}
		ft_free_array(split);
		free(line);
	}
	*ps = (t_coords){INT_MIN, INT_MIN, INT_MIN};
}

char	*init(char *map, t_fdf *fdf)
{
	int	fd;
	int	total_elements;

	if (!ft_contains(map, ".fdf")
		|| ft_strlen(map) < 5 || ft_count_char(map, '.') != 1)
		return (ERROR_EXT);
	if (get_coords(map, &fdf->map_size))
		return (ERROR_MAP);
	total_elements = fdf->map_size.x * fdf->map_size.y + 1;
	fdf->coords = malloc(sizeof(t_coords) * total_elements);
	fdf->original_colors = malloc(sizeof(int) * total_elements);
	fdf->height_colors = malloc(sizeof(int) * total_elements);
	if (!fdf->coords || !fdf->original_colors || !fdf->height_colors)
	{
		free(fdf->coords);
		free(fdf->original_colors);
		free(fdf->height_colors);
		return (ERROR_MALLOC);
	}
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (ERROR_OPEN);
	set_map(fdf, fd);
	close(fd);
	return (NULL);
}

static int	count_and_free(char *line, char separator)
{
	char	**split;
	int		result;
	int		i;

	split = ft_split(line, separator);
	free(line);
	i = -1;
	result = 0;
	while (split[++i])
	{
		free(split[i]);
		result++;
	}
	if (split)
		free(split);
	return (result);
}

static char	*get_coords(char *fdf_path, t_points *map_size)
{
	int		fd;
	char	*line;

	fd = open(fdf_path, O_RDONLY);
	if (fd < 0)
		return (ERROR_OPEN);
	line = get_next_line(fd);
	if (!line)
		return (ERROR_EMP_FD);
	map_size->y = 1;
	map_size->x = count_and_free(line, ' ');
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (count_and_free(line, ' ') != map_size->x)
		{
			close(fd);
			return (ERROR_MAP);
		}
		map_size->y++;
	}
	close(fd);
	return (NULL);
}

static unsigned int	get_color(char *str)
{
	int		color;
	char	*base;

	color = 0xFFFFFF;
	base = "0123456789";
	if (ft_contains(str, ","))
	{
		str = ft_strchr(str, ',') + 1;
		if (ft_strncmp(str, "0x", 2) == 0)
		{
			base = HBASE;
			str += 2;
		}
		color = ft_atoi_base(str, base);
	}
	return (color);
}

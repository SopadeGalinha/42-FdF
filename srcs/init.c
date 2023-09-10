/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:00:48 by jhoonca           #+#    #+#             */
/*   Updated: 2023/09/10 21:40:22 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static char	*get_coords(char *fdf_path, t_points *map_size);
static void	set_map(char *map, t_coords *pos, int *clrs, int *max);

char	*init(char *map, t_fdf *fdf)
{
	int		max[2];

	if (!ft_contains(map, ".fdf") || ft_strlen(map) < 5
		|| ft_count_char(map, '.') != 1)
		return (ERROR_EXT);
	if (get_coords(map, &fdf->map_size))
		return (ERROR_MAP);
	fdf->coords = malloc(sizeof(t_coords) * \
		(fdf->map_size.x * fdf->map_size.y + 1));
	fdf->color = malloc(sizeof(int) * \
		(fdf->map_size.x * fdf->map_size.y + 1));
	fdf->height_colors = malloc(sizeof(int) * \
		(fdf->map_size.x * fdf->map_size.y + 1));
	if (!fdf->coords || !fdf->color || !fdf->height_colors)
	{
		if (fdf->coords)
			free(fdf->coords);
		if (fdf->color)
			free(fdf->color);
		if (fdf->height_colors)
			free(fdf->height_colors);
		return (ERROR_MALLOC);
	}
	max[0] = fdf->map_size.x;
	max[1] = fdf->map_size.y;
	set_map(map, fdf->coords, fdf->color, max);
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
			base = "0123456789abcdef";
			str += 2;
		}
		color = ft_atoi_base(str, base);
	}
	return (color);
}

static void	set_map(char *map, t_coords *pos, int *clrs, int *max)
{
	int		x;
	int		y;
	int		fd;
	char	*line;
	char	**split;

	fd = open(map, O_RDONLY);
	y = -1;
	while (++y < max[1])
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split = ft_split(line, ' ');
		x = -1;
		while (++x < max[0])
		{
			*pos++ = (t_coords){x, y, ft_atoi_base(split[x], "0123456789")};
			*clrs++ = get_color(split[x]);
		}
		ft_free_array(split);
		free(line);
	}
	pos->x = INT_MIN;
	close(fd);
}

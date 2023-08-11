/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 00:44:11 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/11 01:39:08 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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

bool	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool	is_hex(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 'A' && str[i] <= 'F')
			|| (str[i] >= 'a' && str[i] <= 'f'))
			i++;
		else
			return (false);
	}
	return (true);
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -sign;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (base == 16 && str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	if (base == 16 && is_hex(str + i) == false)
		return (0);
	while ((str[i] >= '0' && str[i] <= '9') || \
			(base == 16 && str[i] >= 'A' && str[i] <= 'F') || \
			(base == 16 && str[i] >= 'a' && str[i] <= 'f'))
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			result = result * base + (str[i] - 'A' + 10);
		else if (str[i] >= 'a' && str[i] <= 'f')
			result = result * base + (str[i] - 'a' + 10);
		else
			result = result * base + (str[i] - '0');
		i++;
		if (result < 0)
			return (0);
	}
	return (result * sign);
}

void	set_map( t_fdf *fdf, char *map)
{
	int		fd;
	char	*line;
	char	**split;
	int		i;
	int		j;

	fd = open(map, O_RDONLY);
	fdf->map->coordinates
		= (t_point **)malloc(sizeof(t_point *) * fdf->map->max_y);
	i = 0;
	while (i < fdf->map->max_y)
	{
		fdf->map->coordinates[i]
			= (t_point *)malloc(sizeof(t_point) * fdf->map->max_x);
		j = 0;
		line = get_next_line(fd);
		split = ft_split(line, ' ');
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
		ft_free_split(split);
		free(line);
		i++;
	}
	close(fd);
}

static void	get_dimensions(t_fdf *fdf, int fd)
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

void	ft_initialization(t_fdf *fdf, char *map)
{
	int	fd;

	if (!(ft_strstr(map, ".fdf")) || ft_strlen(map) < 5)
	{
		fdf->error_message = "Error: Invalid file extension\n";
		return ;
	}
	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		fdf->error_message = "Error: open() failed\n";
		return;
	}
	get_dimensions(fdf, fd);
	if (!fdf->error_message)
		set_map(fdf, map);
	close(fd);
}

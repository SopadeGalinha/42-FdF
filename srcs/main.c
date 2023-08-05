/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:18:23 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/05 17:57:18 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fdf.h"

/* void	set_map(t_fdf *fdf, char *file_name)
{
	printf("x: %f y: %f\n", fdf->coordinates->x, fdf->coordinates->y);
	printf("file_name: %s\n", file_name);
}
 */

size_t	ft_arrlen(char **array)
{
	size_t i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void map_read(t_fdf *fdf, int fd)
{
	char	*line;
	unsigned int height;

	line = NULL;
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		ft_printf("line: %s", line);
		height++;
		free(line);
		line = get_next_line(fd);
	}
	fdf->coordinates.z = height;
}

void	ft_initialization(t_fdf *fdf, char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		fdf->error = true;
		fdf->error_message = "Error: open() failed\n";
	}
	map_read(fdf, fd);
	close(fd);
}

int main(int ac, char **av)
{
	t_fdf	fdf;
	if (ac != 2)
		return (write(1, "Error: Invalid number of arguments\n", 35));
	fdf = (t_fdf) {0};
	fdf.coordinates = (t_point) {0};
	ft_initialization(&fdf, av[1]);

	/* fdf.mlx = mlx_init();
	fdf.window = mlx_new_window(fdf.mlx, 500, 500, "FDF");
	mlx_loop(fdf.mlx); */
	return (0);
}

/*
#include "fdf.h"

void	get_width_and_height(int fd, t_fdf *st)
{
	char *line;

	line = NULL;
	if (st->error == 0)
	{			
		line = get_next_line(fd);
		st->width = count_words(line, ' ');
		while (line)
		{
			st->height++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		if (st->height == 0 || st->width == 0)
			st->error = 1;
	}
}

int	ft_atoi(const char *str, t_fdf *st)
{
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + *str++ - '0';
	if (result < 0)
		st->error = 1;
	return (result * sign);
}

void	ft_fill_map(char *file_name, int fd, t_fdf *st)
{
	int		i;
	int		j;
	char	*line;
	char	**split;

	fd = open(file_name, O_RDONLY);
	i = 0;
	while (i < st->height)
	{
		j = 0;
		line = get_next_line(fd);
		split = ft_split(line, ' ');
		while (j < st->width)
		{
			st->map[i][j] = ft_atoi(split[j], st);
			j++;
		}
		free(line);
		i++;
	}
	close(fd);
}

void	ft_read_map(char *file_name, t_fdf *st)
{
	int	i;
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd >= 0)
		get_width_and_height(fd, st);
	close(fd);
	if (st->error == 0)
	{
		st->map = (int **)malloc(sizeof(int *) * (st->height + 1));
		i = 0;
		while (i <= st->height)
			st->map[i++] = (int*)malloc(sizeof(int) * (st->width + 1));
		ft_fill_map(file_name, fd, st);
	}
}

int main(int ac, char **av)
{
	t_fdf	st;

	st.error = 0;
	st.width = 0;
	st.height = 0;
	
	if (ac == 2)
	{	
		ft_read_map(av[1], &st);
		st.mlx = mlx_init();
		st.window = mlx_new_window(st.mlx, 500, 500, "mlx 42");
		mlx_loop(st.mlx);
	}
	return (0);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:18:23 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/06 06:50:37 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fdf.h"

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

static void	is_hexdigit(t_fdf *fdf, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	while (str[i] != '\n')
	{
		if (!ft_isdigit(str[i]) && !ft_strchr("abcdef", ft_tolower(str[i]))){
			fdf->error_message = "Error: invalid color/number\n";
		}
		i++;
	}
}

static void	get_height_width(t_fdf *fdf, int fd)
{
	char	*line;
	char	**split;
	int		i;
	int		j;

	i = 0;
	line = NULL;
	line = get_next_line(fd);
	split = ft_split(line, ' ');
	while (line)
	{
		j = 0;
		while (split[j])
		{
			is_hexdigit(fdf, split[j]);
			j++;
		}
		i++;
		free(line);
		line = get_next_line(fd);
	}
	fdf->coordinates.y = i;
	fdf->coordinates.x = j;
}

void	ft_initialization(t_fdf *fdf, char *map)
{
	int	fd;
	
	if (!(ft_strnstr(map, ".fdf", ft_strlen(map))))
	{
		fdf->error = true;
		fdf->error_message = "Error: Invalid file extension\n";
	}
	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		fdf->error = true;
		fdf->error_message = "Error: open() failed\n";
	}
	else
		get_height_width(fdf, fd);
	close(fd);
	if (fdf->error_message)
		fdf->error = true;
	printf("error_message: %s\n", fdf->error_message);
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
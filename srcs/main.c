/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:18:23 by jhogonca          #+#    #+#             */
/*   Updated: 2023/07/16 04:16:39 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fdf.h"

int main(int ac, char **av)
{	
     void	*mlx;
    void	*window;
	if (ac == 2)
	{	
		//ft_read_map(av[1], &st);
 		mlx = mlx_init();

		window = mlx_new_window(mlx, 500, 500, "mlx 42");
		mlx_loop(mlx);
        ft_atoi("123");
        printf("Arg %s: ", av[1]);
	}
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
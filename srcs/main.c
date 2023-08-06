/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:18:23 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/07 00:08:33 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fdf.h"

static void	is_hexdigit(t_fdf *fdf, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (ft_strstr(str, "0x"))
	{
		while(str[i] && str[i] != ',')
		{
			if (!ft_strchr("0123456789", str[i]))
				fdf->error_message = "Error: Invalid map 1\n";			
			i++;
		}
		i += 3;
		if (!str[i])
			fdf->error_message = "Error: Invalid map 2\n";
		while (str[i] && str[i] != '\n')
		{
			if (!ft_strchr("0123456789ABCDEFabcdef", str[i]))
				fdf->error_message = "Error: Invalid map 3\n";
			i++;
		}
	}
	while (str[i] && str[i] != '\n')
	{
		if (!ft_strchr("0123456789", str[i]))
			fdf->error_message = "Error: Invalid map 3\n";
		i++;
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

static void get_dimensions(t_fdf *fdf, int fd) {
    char *line;
    char **split;
    int i;

    while ((line = get_next_line(fd))) {
        split = ft_split(line, ' ');
        i = 0;
        while (split[i]) {
            is_hexdigit(fdf, split[i]);
            i++;
        }
        if (fdf->coordinates.x == 0) {
            fdf->coordinates.x = i;
        } else if (fdf->coordinates.x != i) {
            fdf->error_message = "Error: Invalid map 4\n";
            break;
        }
        ft_free_split(split);
        free(line);
    }
}

void ft_initialization(t_fdf *fdf, char *map) {
    int fd;

    if (!(ft_strnstr(map, ".fdf", ft_strlen(map)))) {
        fdf->error = true;
        fdf->error_message = "Error: Invalid file extension\n";
        return;
    }

    fd = open(map, O_RDONLY);
    if (fd < 0) {
        fdf->error = true;
        fdf->error_message = "Error: open() failed\n";
        return;
    }

    get_dimensions(fdf, fd);

    close(fd);

	printf("fdf->coordinates.x: %f\n", fdf->coordinates.x);
    if (fdf->error_message) {
        printf("error_message: %s\n", fdf->error_message);
        fdf->error = true;
    }
}

int main(int ac, char **av)
{
	t_fdf	fdf;
	if (ac != 2)
		return (write(1, "Error: Invalid number of arguments\n", 35));
	fdf = (t_fdf) {0};
	fdf.coordinates = (t_point) {0};
	ft_initialization(&fdf, av[1]);
	return (0);
} 
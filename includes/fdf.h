/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 00:31:27 by jhogonca          #+#    #+#             */
/*   Updated: 2023/06/11 06:00:42 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_line
{
	char	*line;
	long	size_line;
	long	index;
	long	size_buffer;
}	t_line;

typedef struct s_data
{
	int				count;
	int				index;
	long			pointer;
	unsigned int	hex_ref;
	char			*str;
}	t_data;

typedef struct s_fdf
{
	int		error;
	int		width;
	int		height;
	int		**map;
    void	*mlx;
    void	*window;
}		t_fdf;

char	*get_next_line(int fd);
int 	count_words(char const *s, char c);
int 	ft_printf(int fd, const char *fmt, ...);
size_t	ft_strlen(char const *s);
char	**ft_split(char const *s, char c);

#endif

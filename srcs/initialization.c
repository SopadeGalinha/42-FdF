/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 02:33:39 by jhoonca           #+#    #+#             */
/*   Updated: 2023/08/06 02:57:00 by jhoonca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void    initialization(t_fdf *fdf, char *map)
{
    int fd;

    if (ft_strrchr(map, ".fdf"))
        printf("fdf file\n");
    else
        printf("not file\n");
    fd = open(map, O_RDONLY);
    if (fd < 0)
    {
        fdf->error = true;
        fdf->error_message = "Error: open() failed\n";
    }
    map_read(fdf, fd);
}
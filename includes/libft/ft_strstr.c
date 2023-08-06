/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:12:02 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/06 21:12:02 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strstr(const char *haystack, const char *needle)
{
	size_t	h;
	size_t	n;

	h = 0;
	n = 0;
	if (needle[n] == 0)
		return (false);
	while (haystack[h])
	{
		while (haystack[h + n] && haystack[h + n] == needle[n])
			n++;
		if (!(needle[n]))
			return (true);
		n = 0;
		h++;
	}
	return (false);
}

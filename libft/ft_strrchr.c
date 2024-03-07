/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:54:27 by mflury            #+#    #+#             */
/*   Updated: 2022/11/30 16:20:36 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// fonction qui fait un strchr depuis la fin de la string s.

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	while ((i + 1) != 0)
	{
		if (s[i] == (char) c)
			return (&((char *)s)[i]);
		else
			i--;
	}
	return (0);
}

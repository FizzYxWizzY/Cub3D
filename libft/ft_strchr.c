/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:21:12 by mflury            #+#    #+#             */
/*   Updated: 2022/11/30 15:21:09 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// fonction qui cherche dans la string s le char c,
// retourne 0 si aucune occurance, sinon renvoie la string 
// depuis la 1ere occurance.

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
		{
			return (&((char *)s)[i]);
		}
		i++;
	}
	if (s[i] == (char) c)
	{
		return (&((char *)s)[i]);
	}
	return (0);
}

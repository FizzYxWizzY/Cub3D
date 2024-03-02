/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:17:59 by mflury            #+#    #+#             */
/*   Updated: 2022/11/30 15:22:04 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// fonction qui duplique une string str avec malloc.

char	*ft_strdup(const char *s)
{
	int		size;
	int		i;
	char	*cpy;

	size = ft_strlen(s);
	cpy = (char *)malloc(sizeof(char) * (size +1));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		*(cpy + i) = *(char *)(s + i);
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

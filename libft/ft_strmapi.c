/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:41:49 by mflury            #+#    #+#             */
/*   Updated: 2022/11/30 15:29:41 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Applique la fonction ’f’ à chaque caractère de la
// chaîne de caractères passée en argument pour créer
// une nouvelle chaîne de caractères (avec malloc(3))
// résultant des applications successives de ’f’.

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*buf;
	size_t	i;

	buf = (char *)ft_calloc(sizeof(char), (ft_strlen(s) + 1));
	if (!buf)
		return (NULL);
	i = 0;
	while (s[i])
	{
		buf[i] = f(i, s[i]);
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

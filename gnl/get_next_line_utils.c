/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:01:51 by mflury            #+#    #+#             */
/*   Updated: 2024/03/02 06:51:50 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// check the lenght of the str.
size_t	ft_strlens(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

// check the lenght of the old string (first time = 0),
// create a new string, copy the old string in it, 
// then add the next char and a '\0' (str_lenght + 2)
// and free the old string.
char	*ft_strjoins(char *str, char c)
{
	size_t	i;
	size_t	str_lenght;
	char	*newstr;

	str_lenght = ft_strlen(str);
	i = 0;
	newstr = malloc(str_lenght + 2);
	if (!newstr)
		return (NULL);
	while (i < str_lenght)
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i++] = c;
	newstr[i] = '\0';
	if (str)
		free(str);
	return (newstr);
}

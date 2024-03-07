/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:54:13 by mflury            #+#    #+#             */
/*   Updated: 2022/12/06 15:14:36 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// sous fonction qui compte les les "mots" dans la string s
// avec un separateur c.

static unsigned int	ft_wcount(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	if (!s[0])
		return (0);
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		count++;
	return (count);
}

// sous fonction qui compte la longeur des "mots" dans la string str
// avec le separateur c, le debut du mot etant str et la fin strlen.

static void	ft_get_row(char **str, unsigned int *strlen, char c)
{
	unsigned int	i;

	*str += *strlen;
	*strlen = 0;
	i = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return ;
		(*strlen)++;
		i++;
	}
}

// sous fonction qui free tout les elements du tabeau tab[i]
// puis le tableau tab lui meme.

static char	**ft_free_all(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

// fonction utilisant les sous fonctions ci dessus pour separer
// les "mots" d une string et de les placer dans un tableau.

char	**ft_split(char const *s, char c)
{
	char			**tab;
	char			*str;
	unsigned int	i;
	unsigned int	strlen;

	tab = ft_calloc(sizeof(char *), (ft_wcount(s, c) + 1));
	if (!tab)
		return (NULL);
	str = (char *)s;
	strlen = 0;
	i = 0;
	while (i < ft_wcount(s, c))
	{
		ft_get_row(&str, &strlen, c);
		tab[i] = ft_calloc(sizeof(char), (strlen + 1));
		if (tab[i] == NULL)
			return (ft_free_all(tab));
		ft_strlcpy(tab[i], str, strlen + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

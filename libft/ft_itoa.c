/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:48:33 by mflury            #+#    #+#             */
/*   Updated: 2022/11/30 15:01:57 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// sous fonction qui ecrit le nbr dans la string
// de droite a gauche.

char	*ft_createtbl(char *x, unsigned int number, long int len)
{
	while (number > 0)
	{
		x[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (x);
}

// sous fonction qui compte la longeur de l int n.

static int	ft_nlen(int n)
{
	int	nlen;

	nlen = 0;
	if (n <= 0)
		nlen = 1;
	while (n != 0)
	{
		n = n / 10;
		nlen++;
	}
	return (nlen);
}

// fonction qui utilise les sous fonctions ci dessus
// pour transformer un int en char.

char	*ft_itoa(int n)
{
	long	ndigit;
	char	*str;

	ndigit = ft_nlen(n);
	str = malloc(sizeof(char) * (ndigit + 1));
	if (!str)
		return (NULL);
	str[ndigit--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str = ft_createtbl(str, n, ndigit);
	return (str);
}

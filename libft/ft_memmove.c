/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:44:23 by mflury            #+#    #+#             */
/*   Updated: 2022/11/30 15:13:23 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// fonction qui deplace la source src dans la destination dst
// sur une longueur n.

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*ptsrc;
	char	*ptdst;

	ptdst = (char *)dst;
	ptsrc = (char *)src;
	if ((ptsrc == NULL) && (ptdst == NULL))
		return (NULL);
	if ((ptsrc < ptdst) && (ptdst < ptsrc + n))
	{
		ptdst += n;
		ptsrc += n;
		while (n)
		{
			*--ptdst = *--ptsrc;
			n--;
		}
	}
	else
	{
		while (n--)
			*ptdst++ = *ptsrc++;
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:13:34 by mflury            #+#    #+#             */
/*   Updated: 2022/11/30 14:41:44 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// fonction qui set a 0 les emplacement d une string sur une longueur donner.

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n * sizeof(char));
}

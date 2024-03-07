/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:59:43 by mflury            #+#    #+#             */
/*   Updated: 2022/11/30 17:40:59 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Alloue (avec malloc(3)) et renvoie un nouvel
// élément. La variable membre ’content’ est
// initialisée à l’aide de la valeur du paramètre
// ’content’. La variable ’next’ est initialisée à
// NULL.

t_list	*ft_lstnew(void *content)
{
	t_list	*bloc;

	bloc = (t_list *)ft_calloc(sizeof(t_list), 1);
	if (!bloc)
	{
		return (NULL);
	}
	bloc->content = content;
	bloc->next = NULL;
	return (bloc);
}

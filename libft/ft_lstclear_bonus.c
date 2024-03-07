/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:38:22 by mflury            #+#    #+#             */
/*   Updated: 2022/11/30 17:44:30 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Supprime et libère la mémoire de l’élément passé en
// paramètre, et de tous les éléments qui suivent, à
// l’aide de ’del’ et de free(3)
// Enfin, le pointeur initial doit être mis à NULL.

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*bloc;

	while (*lst)
	{
		bloc = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = bloc;
	}
	free(*lst);
	*lst = NULL;
}

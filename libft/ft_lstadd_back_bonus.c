/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:08:02 by mflury            #+#    #+#             */
/*   Updated: 2022/11/30 16:24:32 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Ajoute l’élément ’new’ à la fin de la liste.

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*bloc;

	bloc = ft_lstlast(*lst);
	if (!bloc)
		*lst = new;
	else
		bloc->next = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:22:28 by mflury            #+#    #+#             */
/*   Updated: 2022/11/30 15:15:21 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// fonction qui ecrit dans le file descriptor fd le char c.

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

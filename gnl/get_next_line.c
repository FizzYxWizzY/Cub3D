/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:01:40 by mflury            #+#    #+#             */
/*   Updated: 2024/03/02 06:52:31 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// read(int fd, void *buf, size_t count);
//			fd from where we read.
// 					 buffer of the read.
//									size
// return the number of char read, -1 if there is a problem reading.

// function that return the content char by char.
// return 0 if there is no content to read.
// return -1 if there is a problem reading fd.
char	ft_getchar(t_gnl *gnl)
{
	char	c;

	if (gnl->pos >= gnl->maxsize)
	{
		gnl->pos = 0;
		gnl->maxsize = read(gnl->fd, gnl->content, BUFFER_SIZE);
		if (gnl->maxsize == 0)
			return (0);
		if (gnl->maxsize == -1)
			return (-1);
	}
	c = gnl->content[gnl->pos];
		gnl->pos++;
	return (c);
}

//initialise the struct.

int	ft_init(t_gnl *gnl, int fd)
{
	gnl->fd = fd;
	gnl->pos = 0;
	gnl->maxsize = read(gnl->fd, gnl->content, BUFFER_SIZE);
	if (gnl->maxsize <= 0)
		return (0);
	return (1);
}

// create a static struct (t_gnl gnl) and set its fd to -1 (not set yet),
// set the fd of the struct (on the first time) with ft_init,
// read in the fd and put it in content, then return content char by char.
// copy char in line until until it encounter a \n, return line. 
char	*get_next_line(int fd)
{
	static t_gnl	gnl = {.fd = -1};
	char			c;
	char			*line;

	line = NULL;
	if (gnl.fd != fd)
	{
		if (ft_init(&gnl, fd) != 1)
			return (NULL);
	}
	c = ft_getchar(&gnl);
	while (c)
	{
		if (c == -1)
		{
			if (line)
				free(line);
			return (NULL);
		}
		line = ft_strjoins(line, c);
		if (c == '\n')
			return (line);
		c = ft_getchar(&gnl);
	}
	return (line);
}

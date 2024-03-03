/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:21:02 by mflury            #+#    #+#             */
/*   Updated: 2024/03/03 03:31:00 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_file	file;
	char	*line;
	
	if (argc > 2)
		error("too much arguments.");
	if (argc < 2)
		error("need the map path as argument.");
	if (path_check(argv[1]) != 0)
		error("map path is trash.");
	file.fd = open(argv[1], O_RDONLY);
	if (file.fd < 0)
		error("Can't open file");
	line = get_next_line(file.fd);
	While (line)
	{
		line_check(line, &file);
		free(line);
		line = get_next_line(file.fd);
		if (file->textures.count == 6)
		{
			free(line);
			break ;
		}
	}
	return EXIT_SUCCESS;
}

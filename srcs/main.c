/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:21:02 by mflury            #+#    #+#             */
/*   Updated: 2024/03/04 07:24:23 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_data(t_file *file)
{
	file->fd = -1;
	file->textures.count = 0;
	file->textures.north = NULL;
	file->textures.south = NULL;
	file->textures.west = NULL;
	file->textures.east = NULL;
	file->textures.floor[0] = -1;
	file->textures.floor[1] = -1;
	file->textures.floor[2] = -1;
	file->textures.ceiling[0] = -1;
	file->textures.ceiling[1] = -1;
	file->textures.ceiling[2] = -1;
	file->map = NULL;
}

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
	init_data(&file);
	line = get_next_line(file.fd);
	while (line)
	{
		line_check(line, &file);
		free(line);
		if (file.textures.count == 6)
			break ;
		line = get_next_line(file.fd);
	}
	if (file.textures.count != 6)
		error("missing texture(s)");
	return EXIT_SUCCESS;
}

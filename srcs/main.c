/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:21:02 by mflury            #+#    #+#             */
/*   Updated: 2024/08/08 03:26:23 by mflury           ###   ########.fr       */
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

void	free_all(t_file *file)
{
	if (file->textures.north)
		free(file->textures.north);
	if (file->textures.south)
		free(file->textures.south);
	if (file->textures.east)
		free(file->textures.east);
	if (file->textures.west)
		free(file->textures.west);
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
	init_data(&file);
	file.fd = open(argv[1], O_RDONLY);
	if (file.fd < 0)
		error("Can't open file.");
	line = get_next_line(file.fd);
	while (line)
	{
		line_check(line, &file);
		free(line);
		if (file.textures.count == 6)
			break ;
		line = get_next_line(file.fd);
	}
	if (file.textures.count != 6) {
		free_all(&file);
		error("missing texture(s).");
	}
	printf("texture north: %s\n", file.textures.north);
	printf("texture south: %s\n", file.textures.south);
	printf("texture east: %s\n", file.textures.east);
	printf("texture west: %s\n", file.textures.west);
	printf("texture floor: [%d,%d,%d]\n", file.textures.floor[0], file.textures.floor[1], file.textures.floor[2]);
	printf("texture ceiling: [%d,%d,%d]\n",  file.textures.ceiling[0], file.textures.ceiling[1], file.textures.ceiling[2]);
	printf("texture count: %d\n", file.textures.count);
	free_all(&file);
	return EXIT_SUCCESS;
}

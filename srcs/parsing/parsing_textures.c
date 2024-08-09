/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:32:42 by mflury            #+#    #+#             */
/*   Updated: 2024/08/09 09:33:42 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	check_args(int argc, char **argv, t_file *file)
{
	if (argc > 2)
		error("too much arguments.");
	if (argc < 2)
		error("need the map path as argument.");
	if (path_check(argv[1]) != 0)
		error("map path is trash.");
	file->fd = open(argv[1], O_RDONLY);
	if (file->fd < 0)
		error("Can't open file.");
	
}

void	set_textures(t_file *file)
{
	char	*line;

	line = get_next_line(file->fd);
	while (line)
	{
		line_check(line, file);
		free(line);
		if (file->textures.count == 6)
			break ;
		line = get_next_line(file->fd);
	}
	if (file->textures.count != 6) {
		free_all(file);
		error("missing texture(s).");
	}
}

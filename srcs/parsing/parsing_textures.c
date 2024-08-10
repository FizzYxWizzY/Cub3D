/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:32:42 by mflury            #+#    #+#             */
/*   Updated: 2024/08/10 04:59:32 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	check_args(int argc, char **argv, t_file *file)
{
	int i;

	i = 0;
	if (argc > 2)
		error("too much arguments.");
	if (argc < 2)
		error("need the map path as argument.");
	if (path_check(argv[1]) != 0)
		error("not a map.cub.");
	file->fd = open(argv[1], O_RDONLY);
	if (file->fd < 0)
		error("Can't open file.");
	file->mappath = malloc(sizeof(char) * ft_strlen(argv[1]) + 1);
	while (argv[1][i])
		file->mappath[i] = argv[1][i++];
	file->mappath[i] = '\0';
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

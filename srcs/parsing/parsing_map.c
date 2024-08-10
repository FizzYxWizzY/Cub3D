/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:34:38 by mflury            #+#    #+#             */
/*   Updated: 2024/08/10 05:02:36 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


//  look if its the 1st line of the map.
int	is_map_start(char *line)
{
	int i;
	int one_count;

	i = 0;
	one_count = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' || line[i] != '1')
			return 0;
		if ( line[i] == '1')
			++one_count;
		++i;
	}
	if (one_count > 0)
		return 1;
	return 0;
}

void	set_map_size(t_file *file)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (!is_map_start(line))
		get_next_line(file->fd);
	while (line)
	{
		if (ft_strlen(line) > file->maxlength)
			file->maxlength = ft_strlen(line);
		++file->maplinecount;
		get_next_line(file->fd);
	}
	close(file->fd);
	file->map = malloc(sizeof(char *) * file->maplinecount + 2);
	file->map[file->maplinecount + 1] = '\0';
	while (i < file->maplinecount + 2)
	{
		file->map[i] = malloc(sizeof(char) * file->maxlength + 2);
		ft_memset(file->map[i], ' ', file->maxlength + 2);
		file->map[i][file->maxlength + 1] = '\0';
		++i;
	}
}

void fill_map(t_file *file)
{
	int	i;
	int	j;
	char	*line;

	i = 1;
	j = 0;
	line = NULL;
	open(file->mappath, O_RDONLY);
	while (!is_map_start(line))
		get_next_line(file->fd);
	while (line)
	{
		while (line[j])
			file->map[i][j + 1] = line[j++];
		++i;
		j = 0;
		get_next_line(file->fd);
	}
}


void	set_map(t_file *file)
{
	set_map_size(file);
	fill_map(file);
}

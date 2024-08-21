/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:34:38 by mflury            #+#    #+#             */
/*   Updated: 2024/08/16 01:29:30 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


void	start_count(t_file *file)
{
	int	count;
	size_t x;
	int y;

	count = 0;
	x = 0;
	y = 0;
	while (y < file->maplinecount + 2)
	{
		while (x < file->maxlength + 2)
		{
			if (file->map[y][x] == 'N' || file->map[y][x] == 'S'
				|| file->map[y][x] == 'E' || file->map[y][x] == 'W')
				++count;
			++x;
		}
		++y;
		x = 0;
	}
	if (count != 1)
	{
		free_all(file);
		error("it needs to only have one starting position on the map.");
	}
}

//  look if its the 1st line of the map.
int	is_map_start(char *line)
{
	int i;
	int one_count;

	i = 0;
	one_count = 0;
	if (line)
	{
		if (line[i] == ' ' || line[i] == '1' || line[i] == '0' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			while (line[i] == ' ' || line[i] == '1' || line[i] == '0'
				|| line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'W')
			{
				if(line[i++] == '1')
					one_count++;
			}
			if ((line[i] == '\n' || !line[i]) && one_count > 0)
				return 1;
		}
	}
	return 0;
}

char	*find_map_start(t_file *file)
{
	char	*line;

	line = NULL;
	line = get_next_line(file->fd);
	while (!is_map_start(line))
	{
		free(line);
		line = get_next_line(file->fd);
		if (!line)
			break;
	}
	return line;
}

void	set_map_size(t_file *file)
{
	int		i;
	char	*line;

	i = 0;
	line = find_map_start(file);
	while (line)
	{
		if (ft_strlen(line) > file->maxlength)
			file->maxlength = ft_strlen(line);
		++file->maplinecount;
		free(line);
		line = get_next_line(file->fd);
	}
	free(line);
	close(file->fd);
	file->fd = open(file->mappath, O_RDONLY);
	file->map = malloc(sizeof(char *) * (file->maplinecount + 2));
	file->map[file->maplinecount + 1] = NULL;
	while (i < (file->maplinecount + 2))
	{
		file->map[i] = malloc(sizeof(char) * (file->maxlength + 2));
		ft_memset(file->map[i], ' ', file->maxlength + 2);
		file->map[i++][file->maxlength + 1] = '\0';
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
	while (!is_map_start(line))
	{
		free(line);
		line = get_next_line(file->fd);
	}
	while (line)
	{
		while (line[j])
		{
			if (line[j] != '\n')
				file->map[i][j + 1] = line[j];
			++j;
		}
		++i;
		j = 0;
		free(line);
		line = get_next_line(file->fd);
	}
	free(line);
}

void	set_map(t_file *file)
{
	set_map_size(file);
	fill_map(file);
	if (!is_valid_char_only(file))
	{
		free_all(file);
		error("invalid char in map.");
	}
	start_count(file);
	is_closed_map(file);
}

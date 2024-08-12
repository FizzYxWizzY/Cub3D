/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:34:38 by mflury            #+#    #+#             */
/*   Updated: 2024/08/12 02:48:16 by mflury           ###   ########.fr       */
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
	// printf("is_map_start:\nline: '%s'\n", line);
	if (line)
	{
		if (line[i] == ' ' || line[i] == '1' || line[i] == '0')
		{
			while (line[i] == ' ' || line[i] == '1' || line[i] == '0')
			{
				if(line[i++] == '1')
					one_count++;
			}
			if ((line[i] == '\n' || !line[i]) && one_count > 0)
			{
				printf("map start found!\n");
				return 1;
			}
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
	file->fd = open(file->mappath, O_RDONLY);
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
	int	i;
	set_map_size(file);
	fill_map(file);
	i = 0;
	while (i < (file->maplinecount + 2))
		printf("map: '%s'\n", file->map[i++]);	
}

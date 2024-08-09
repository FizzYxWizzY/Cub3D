/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:55:50 by mflury            #+#    #+#             */
/*   Updated: 2024/08/09 09:58:17 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// im paid by the char, xoxo

// why would i think if it works fine without thinking?

void	verify_paths(t_file *file)
{
	if(open(file->textures.north, O_RDONLY) == -1)
	{
		free_all(file);
		error("north texture not found.");
	}
	if(open(file->textures.south, O_RDONLY) == -1)
	{
		free_all(file);
		error("south texture not found.");
	}
	if(open(file->textures.east, O_RDONLY) == -1)
	{
		free_all(file);
		error("east texture not found.");
	}
	if(open(file->textures.west, O_RDONLY) == -1)
	{
		free_all(file);
		error("west texture not found.");
	}
}

void	set_colors(int *tab, char *line)
{
	int	i;
	char **codes;
	char *start;

	i = 0;
	while (line[i] == 'F' || line[i] == 'C' ||
		line[i] == ' ' || line[i] == '\t')
		i++;
	start = &line[i];
	codes = ft_split(start, ',');
	i = 0;
	while (codes[i])
	{
		if (ft_atoi(codes[i]) < 0 || ft_atoi(codes[i]) > 255)
		{
			while (codes[i])
				free(codes[i++]);
			free(codes);
			error("RGB value out of range. (0-255)");
		}
		tab[i] = ft_atoi(codes[i]);
		free(codes[i++]);
	}
	free(codes);
}

char	*set_path(char *line)
{
	int		i;
	int		j;
	int		k;
	char *path;

	i = 0;
	j = 0;
	k = 0;
	while (line[i] == 'N' || line[i] == 'O' || line[i] == 'S' ||
		line[i] == 'W' || line[i] == 'E' || line[i] == 'A' ||
		line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i + j])
		j++;
	path = malloc(sizeof(char) * (j + 1));
	while (line[i] && line[i] != '\n' && line[i] != ' ' && line[i] != '\t')
		path[k++] = line[i++];
	path[k] = '\0';
	printf("brut line: \"%s\"\n", line);
	printf("sanitized path: \"%s\"\n", path);
	return (path);
}

void	line_check(char *line, t_file *file)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N')
		file->textures.north = set_path(line);
	else if (line[i] == 'S')
		file->textures.south = set_path(line);
	else if (line[i] == 'W')
		file->textures.west = set_path(line);
	else if (line[i] == 'E')
		file->textures.east = set_path(line);
	else if (line[i] == 'F')
		set_colors(file->textures.floor, line);
	else if (line[i] == 'C')
		set_colors(file->textures.ceiling, line);
	else
		return ;
	file->textures.count++;
}

// i wont turn on my brain! i wont turn on my brain! i wont turn on my brain!

int	path_check(char *map_path)
{
	int	i;

	i = 0;
	while (map_path[i])
	{
		if (map_path[i] == '.' && map_path[i + 1] != '\0')
			if (map_path[i + 1] == 'c' && map_path[i + 2] != '\0')
				if (map_path[i + 2] == 'u' && map_path[i + 3] != '\0')
					if (map_path[i + 3] == 'b' && map_path[i + 4] == '\0')
						return 0;
		i++;
	}
	return 1;
}

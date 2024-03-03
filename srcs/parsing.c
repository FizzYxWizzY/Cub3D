/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:40:25 by mflury            #+#    #+#             */
/*   Updated: 2024/03/03 02:29:18 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// im paid by the char, tbh... xoxo

void	set_color(int *tab, char *line)
{
	int	i;
	char **codes;
	char *start;

	i = 0;
	while (line[i] == 'F' || line[i] == 'C' || line[i] == ' ' || line[i] == '\t')
		i++;
	start = line[i];
	codes = ft_split(start, ',');
	i = 0;
	while (codes[i])
	{
		tab[i] = ft_atoi(codes[i]);
		i++;
	}
}

void	set_path(char *path, char *line)
{
	int		i;
	int		j;
	int		k;
	char	*texture;

	i = 0;
	j = 0;
	k = 0;
	while (line[i] == 'N' || line[i] == 'O' || line[i] == 'S' ||
		line[i] == 'W' || line[i] == 'E' || line[i] == 'A' ||
		line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i + j])
		j++;
	texture = malloc(sizeof(char) * (j + 1));
	while (i <= j)
		texture[k++] = line[i++];
	path = &texture;
}

void	line_check(char *line, t_file *file)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N')
		set_path(file->textures.north, line);
	if (line[i] == 'S')
		set_path(file->textures.south, line);
	if (line[i] == 'W')
		set_path(file->textures.west, line);
	if (line[i] == 'E')
		set_path(file->textures.east, line);
	if (line[i] == 'F')
		set_color(file->textures.floor, line);
	if (line[i] == 'C')
		set_color(file->textures.ceiling, line);
}

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

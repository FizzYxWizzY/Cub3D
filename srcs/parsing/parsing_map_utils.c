/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:56:22 by mflury            #+#    #+#             */
/*   Updated: 2024/08/13 20:05:38 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// verify that the map is only composed of valid char (0,1,N,S,E,W)
// make a copy of the map.
// find the starting position for the floodfill (player starting pos {N,S,E,W}).
// floodfill the map (stops if it encounter a '1', write '1' on checked index, error if it reach a ' ').
// delete the map copy

// x = horizontal y = vertical.


int	is_valid_char_only(t_file *file)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < (file->maplinecount + 2))
	{
		while (j < (file->maxlength + 2))
		{
			if (file->map[i][j] != ' ' && file->map[i][j] != '0'
				&& file->map[i][j] != '1' && file->map[i][j] != 'N'
				&& file->map[i][j] != 'S' && file->map[i][j] != 'E'
				&& file->map[i][j] != 'W' && file->map[i][j] != '\0')
				return 0;
			j++;
		}
		i++;
		j = 0;
	}
	return 1;
}

char	**copy_map(t_file *file)
{
	int		i;
	size_t	j;
	char	**copy;

	i = 0;
	j = 0;
	copy = malloc(sizeof(char *) * (file->maplinecount + 2));
	while (i < (file->maplinecount + 2))
	{
		copy[i] = malloc(sizeof(char) * (file->maxlength + 2));
		while (j < (file->maxlength + 2))
		{
			copy[i][j] = file->map[i][j];
			j++;
		}
		i++;
		j = 0;
	}
	return copy;
}

void	floodfill(char **map, t_file *file, size_t x, int y)
{
	if (map[y][x] == '1' || map[y][x] == ' ')
	{
		if (map[y][x] == ' ')
			printf("map fucked up. (map[%d][%ld])\n", y, x);
		return ;
	}
	map[y][x] = '1';
	floodfill(map, file, x + 1, y);
	floodfill(map, file, x, y + 1);
	floodfill(map, file, x - 1, y);
	floodfill(map, file, x, y - 1);
}

size_t	get_start_x(char **map, t_file *file)
{
	size_t	x;
	int		y;

	x = 0;
	y = 0;
	while (y < (file->maplinecount + 2))
	{
		while (x < (file->maxlength + 2))
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
				return x;
			++x;
		}
		++y;
		x = 0;
	}
	return 0;
}

int	get_start_y(char **map, t_file *file)
{
	size_t	x;
	int		y;

	x = 0;
	y = 0;
	while (y < (file->maplinecount + 2))
	{
		while (x < (file->maxlength + 2))
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
				return y;
			++x;
		}
		++y;
		x = 0;
	}
	return 0;
}

void	free_copy(char **map, t_file *file)
{
	int	i;

	i = 0;
	while (i < (file->maplinecount + 2))
		free(map[i++]);
	free(map);
}

void	print_map_copy(char **map, t_file *file)
{
	int		y;

	y = 0;
	while (y < (file->maplinecount + 2))
	{
		printf("floodfill: '%s'\n", map[y++]);
	}
}

void	is_closed_map(t_file *file)
{
	char **map;
	size_t	x;
	int		y;

	map = copy_map(file);
	x = get_start_x(map, file);
	if (x == 0)
	{
		free_copy(map, file);
		free_all(file);
		error("cant find start player x for floodfill.");
	}
	y = get_start_y(map, file);
	if (x == 0)
	{
		free_copy(map, file);
		free_all(file);
		error("cant find start player y for floodfill.");
	}
	floodfill(map, file, x, y);
	print_map_copy(map, file); // should not go in prod.
	free_copy(map, file);
}

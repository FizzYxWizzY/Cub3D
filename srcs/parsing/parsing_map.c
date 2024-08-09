/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:34:38 by mflury            #+#    #+#             */
/*   Updated: 2024/08/09 13:55:53 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	map_start(char *line)
{
	int i;
	int one_count;

	i = 0;
	one_count = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' || line[i] != '1')
		if ( line[i] == '1')
			++one_count;
		++i;
	}
}


void	set_map(t_file *file)
{
	int max_line_lenth = 0;
	int max_line_count = 0;

	get_next_line(file->fd);
	is_map(file);
	if line is only ' ' && mini 1x '1' == debut map.
	{
			while(line)
			{
				ft_strlen(line);
			}
	}
}


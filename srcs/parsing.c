/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:40:25 by mflury            #+#    #+#             */
/*   Updated: 2024/03/02 22:31:05 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

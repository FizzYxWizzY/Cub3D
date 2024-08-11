/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:21:02 by mflury            #+#    #+#             */
/*   Updated: 2024/08/10 22:31:23 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// classic init shit...

void	init_data(t_file *file)
{
	file->fd = -1;
	file->mappath = NULL;
	file->textures.count = 0;
	file->textures.north = NULL;
	file->textures.south = NULL;
	file->textures.west = NULL;
	file->textures.east = NULL;
	file->textures.floor[0] = -1;
	file->textures.floor[1] = -1;
	file->textures.floor[2] = -1;
	file->textures.ceiling[0] = -1;
	file->textures.ceiling[1] = -1;
	file->textures.ceiling[2] = -1;
	file->map = NULL;
	file->maplinecount = 0;
	file->maxlength = 0;
}

// I MUST NOT DO THE SO_LONG SHIT AGAIN!!!!!!!!!!!!!!!!!! (lies)

void	free_all(t_file *file)
{
	if (file->textures.north)
		free(file->textures.north);
	if (file->textures.south)
		free(file->textures.south);
	if (file->textures.east)
		free(file->textures.east);
	if (file->textures.west)
		free(file->textures.west);
	if (file->mappath)
		free(file->mappath);
}

int	main(int argc, char **argv)
{
	t_file	file;

	parse_file(argc, argv, &file);
	
	// int i = 0;
	// while (file.map[i])
	// {
	// 	printf("%s\n", file.map[i]);
	// 	free(file.map[i]);
	// 	++i;
	// }
	// free(file.map);
	
	// TO BE DELETED
	// printf("texture north: %s\n", file.textures.north);
	// printf("texture south: %s\n", file.textures.south);
	// printf("texture east: %s\n", file.textures.east);
	// printf("texture west: %s\n", file.textures.west);
	// printf("texture floor: [%d,%d,%d]\n", file.textures.floor[0], file.textures.floor[1], file.textures.floor[2]);
	// printf("texture ceiling: [%d,%d,%d]\n",  file.textures.ceiling[0], file.textures.ceiling[1], file.textures.ceiling[2]);
	// printf("texture count: %d\n", file.textures.count);
	//

	free_all(&file);
	return EXIT_SUCCESS;
}

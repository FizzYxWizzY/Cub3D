/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:40:25 by mflury            #+#    #+#             */
/*   Updated: 2024/10/21 08:58:26 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	parse_file(int argc, char **argv, t_file *file)
{
	// int i = 0;
	// set default values for all the file struct.
	init_data(file);

	// check args, set the path of all the textures and the colors,
	// then verify that they exists.
	check_args(argc, argv, file);
	set_textures(file);
	verify_paths(file);
	
	// find and copy the map in the file->mapstruct
	set_map(file);
	// i = 0;
	// while (i < (file->maplinecount + 2))
		// printf("map: '%s'\n", file->map[i++]);
	// printf("line count: %d\nline max lenght: %ld\n", file->maplinecount, file->maxlength);


}

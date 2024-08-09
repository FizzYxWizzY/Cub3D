/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:40:25 by mflury            #+#    #+#             */
/*   Updated: 2024/08/09 13:23:01 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	parse_file(int argc, char **argv, t_file *file)
{
	check_args(argc, argv, file);
	set_textures(file);
	verify_paths(file);
	// set_map(file);
}
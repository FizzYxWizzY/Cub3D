/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_trgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:44:02 by mflury            #+#    #+#             */
/*   Updated: 2024/09/01 12:36:23 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// t = 0, rgb = file.ceiling[3] & file.floor[3];

int	create_trgb(int r, int g, int b)
{
	return (0 << 24 | r << 16 | g << 8 | b);
}

void	set_trgb_all(t_file *file)
{
	file->textures.trgb_ceiling = create_trgb(file->textures.ceiling[0],
		file->textures.ceiling[1], file->textures.ceiling[2]);
	file->textures.trgb_floor = create_trgb(file->textures.floor[0],
		file->textures.floor[1], file->textures.floor[2]);
}

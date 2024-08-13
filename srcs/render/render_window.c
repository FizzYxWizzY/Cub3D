/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 02:09:18 by mflury            #+#    #+#             */
/*   Updated: 2024/08/14 00:35:49 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// x = horizontal y = vertical.

// void	print_minimap(t_mlx *mlx, t_file *file)
// {
	
// }

void	create_window(t_mlx *mlx, t_file *file)
{
	mlx->mlx = mlx_init();
	(void) file;

	mlx->mlx_win = mlx_new_window(mlx->mlx, (file->maxlength + 2) * 10, (file->maplinecount + 2) * 10, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx, (file->maxlength + 2) * 10, (file->maplinecount + 2) * 10);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	size_t x = 0;
	int y = 0;
	
	// while (x < file->maxlength + 2)
	// {
	// 	while (y < file->maplinecount + 2)
	// 	{
	// 		if (file->map[])
	// 		++y;
	// 	}
	// 	++x;
	// }
	while (x < ((file->maxlength + 2) * 10))
	{
		if (x % 10 != 0)
		{
			while (y < ((file->maplinecount + 2) * 10))
			{
				if ((y % 10) != 0)
				{
					if (file->map[y / 10][x / 10] == '1')
						mlx_pixel_put(mlx->mlx, mlx->mlx_win, x, y++, 0xc20404);
					else if (file->map[y / 10][x / 10] == '0')
						mlx_pixel_put(mlx->mlx, mlx->mlx_win, x, y++, 0x00ff44);
					else if (file->map[y / 10][x / 10] == ' ')
						mlx_pixel_put(mlx->mlx, mlx->mlx_win, x, y++, 0xffdd00);
					else
						++y;
				}
				else
					mlx_pixel_put(mlx->mlx, mlx->mlx_win, x, y++, 0x000000);
			}	
		}
		else
			while (y < (file->maplinecount + 2) * 10)
				mlx_pixel_put(mlx->mlx, mlx->mlx_win, x, y++, 0x000000);
		x++;
		y = 0;
	}
	mlx_loop(mlx->mlx);
}
                                            
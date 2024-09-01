/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 02:09:18 by mflury            #+#    #+#             */
/*   Updated: 2024/09/01 14:14:41 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// x = horizontal y = vertical.

// void	draw_minimap(t_mlx *mlx, t_file *file)
// {
// 	size_t x = 0;
// 	int y = 0;

// 	draw_background(mlx, file);

// 	while (x < ((file->maxlength + 2) * 10))
// 	{
// 		if (x % 10 != 0)
// 		{
// 			while (y < ((file->maplinecount + 2) * 10))
// 			{
// 				if ((y % 10) != 0)
// 				{
// 					if (file->map[y / 10][x / 10] == '1')
// 						mlx_put_pixel_to_image(mlx, x, y++, 0x00c20404); // rouge
// 					else if (file->map[y / 10][x / 10] == '0' || file->map[y / 10][x / 10] == 'N'
// 						|| file->map[y / 10][x / 10] == 'S' || file->map[y / 10][x / 10] == 'W'
// 						|| file->map[y / 10][x / 10] == 'E')
// 						mlx_put_pixel_to_image(mlx, x, y++, 0x0000ff44); // vert
// 					else if (file->map[y / 10][x / 10] == ' ')
// 						mlx_put_pixel_to_image(mlx, x, y++, 0x00ffdd00); // jaune

// 					else
// 						++y;
// 				}
// 				else
// 					mlx_put_pixel_to_image(mlx, x, y++, 0x00000000);
// 			}	
// 		}
// 		else
// 			while (y < (file->maplinecount + 2) * 10)
// 				mlx_put_pixel_to_image(mlx, x, y++, 0x00000000);
// 		x++;
// 		y = 0;
// 	}
// 	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
// }

void	draw_background(t_mlx *mlx, t_file *file)
{
	int		y;
	size_t	x;

	y = 0;
	x = 0;
	while (y < 768)
	{
		while (y < 768)
		{
			while (x < 1366)
			{
				if (y < (768 / 2))
					mlx_put_pixel_to_image(mlx, x++, y, file->textures.trgb_ceiling);
				else
					mlx_put_pixel_to_image(mlx, x++, y, file->textures.trgb_floor);
			}
			x = 0;
			++y;
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0); // needs better management later
}

void	create_window(t_mlx *mlx, t_file *file)
{
	(void)file;
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 1366, 768, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx, 1366, 768);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
}
                                            
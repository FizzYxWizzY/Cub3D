/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 02:09:18 by mflury            #+#    #+#             */
/*   Updated: 2024/08/22 01:55:32 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// x = horizontal y = vertical.

void	draw_minimap(t_mlx *mlx, t_file *file)
{
	size_t x = 0;
	int y = 0;
	
	while (x < ((file->maxlength + 2) * 10))
	{
		if (x % 10 != 0)
		{
			while (y < ((file->maplinecount + 2) * 10))
			{
				if ((y % 10) != 0)
				{
					if (file->map[y / 10][x / 10] == '1')
						mlx_put_pixel_to_image(mlx, 1 + x, 1 + y++, 0x00c20404); // rouge
					else if (file->map[y / 10][x / 10] == '0' || file->map[y / 10][x / 10] == 'N' || file->map[y / 10][x / 10] == 'S' || file->map[y / 10][x / 10] == 'W' || file->map[y / 10][x / 10] == 'E')
						mlx_put_pixel_to_image(mlx, 1 + x, 1 + y++, 0x0000ff44); // vert
					else if (file->map[y / 10][x / 10] == ' ')
						mlx_put_pixel_to_image(mlx, 1 + x, 1 +  y++, 0x00ffdd00); // jaune

					else
						++y;
				}
				else
					mlx_put_pixel_to_image(mlx, 1 + x, 1 + y++, 0x00000000);
			}	
		}
		else
			while (y < (file->maplinecount + 2) * 10)
				mlx_put_pixel_to_image(mlx, 1 + x, 1 + y++, 0x00000000);
		x++;
		y = 0;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
}

void	create_window(t_mlx *mlx, t_file *file)
{
	size_t x;
	int y;

	x = 0;
	y = 0;
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 1366, 768, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx, (file->maxlength + 1) * 10, (file->maplinecount + 2) * 10);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	// PRIS D UNE SOUDAINE ENVIE DE SE FOUTRE EN L AIR ALED!
	while (x < ((file->maxlength + 2) * 10))
	{
		if (x % 10 != 0)
		{
			while (y < ((file->maplinecount + 2) * 10))
			{
				if ((y % 10) != 0)
				{
					if (file->map[y / 10][x / 10] == '1')
						mlx_put_pixel_to_image(mlx, 1 + x, 1 + y++, 0x00c20404); // rouge
					else if (file->map[y / 10][x / 10] == '0' || file->map[y / 10][x / 10] == 'N' || file->map[y / 10][x / 10] == 'S' || file->map[y / 10][x / 10] == 'W' || file->map[y / 10][x / 10] == 'E')
						mlx_put_pixel_to_image(mlx, 1 + x, 1 + y++, 0x0000ff44); // vert
					else if (file->map[y / 10][x / 10] == ' ')
					{
						// mlx_put_pixel_to_image(mlx, 1 + x, 1 + y++, 0x0000ff44);
						mlx_put_pixel_to_image(mlx, 1 + x, 1 +  y++, 0x00ffdd00); // jaune
					}
					else
						++y;
				}
				else
					mlx_put_pixel_to_image(mlx, 1 + x, 1 + y++, 0x00000000);
			}	
		}
		else
			while (y < (file->maplinecount + 2) * 10)
				mlx_put_pixel_to_image(mlx, 1 + x, 1 + y++, 0x00000000);
		x++;
		y = 0;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	draw_minimap(mlx, file);
	// mlx_hook(mlx->mlx_win, ON_KEYDOWN, 0, keeb_listener, &mlx);
	mlx_loop(mlx->mlx);
}
                                            
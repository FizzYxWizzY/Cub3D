/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:21:02 by mflury            #+#    #+#             */
/*   Updated: 2024/03/23 13:52:26 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	init_data(t_file *file)
// {
// 	file->fd = -1;
// 	file->textures.count = 0;
// 	file->textures.north = NULL;
// 	file->textures.south = NULL;
// 	file->textures.west = NULL;
// 	file->textures.east = NULL;
// 	file->textures.floor[0] = -1;
// 	file->textures.floor[1] = -1;
// 	file->textures.floor[2] = -1;
// 	file->textures.ceiling[0] = -1;
// 	file->textures.ceiling[1] = -1;
// 	file->textures.ceiling[2] = -1;
// 	file->map = NULL;
// }

// int	main(int argc, char **argv)
// {
// 	t_file	file;
// 	char	*line;
	
// 	if (argc > 2)
// 		error("too much arguments.");
// 	if (argc < 2)
// 		error("need the map path as argument.");
// 	if (path_check(argv[1]) != 0)
// 		error("map path is trash.");
// 	file.fd = open(argv[1], O_RDONLY);
// 	if (file.fd < 0)
// 		error("Can't open file");
// 	init_data(&file);
// 	line = get_next_line(file.fd);
// 	while (line)
// 	{
// 		line_check(line, &file);
// 		free(line);
// 		if (file.textures.count == 6)
// 			break ;
// 		line = get_next_line(file.fd);
// 	}
// 	if (file.textures.count != 6)
// 		error("missing texture(s)");
// 	return EXIT_SUCCESS;
// }

// ARTHUR partie ====================================================

int	main(void)
{
	t_data	img;
	
	img.mlx = mlx_init();
	initPlayerStruct(&img.player);
	img.win = mlx_new_window(img.mlx, sWidth, sHeight, "Hello world!");
	img.img = mlx_new_image(img.mlx, sWidth, sHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
							&img.endian);
	// while (1)
	// {
		drawSky(&img);
		drawGround(&img);
		if (!drawMap(&img))
			{
				printf("error map\n");
				// break;
			}
		drawPlayerPos(&img,img.player.x, img.player.y);
		mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
		mlx_hook(img.win, 2, 2, key_hook, &img);
		mlx_loop(img.mlx);
	// }
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 2)
	{
		data->player.rA += 0.1; // tourner
		if (data->player.rA > 2 * M_PI)
			data->player.rA -= 2 * M_PI;
	}
	else if (keycode == 0)
	{
		data->player.rA -= 0.1;
		if (data->player.rA < 0)
			data->player.rA += 2 * M_PI;
	}
	data->player.dirX = cos(data->player.rA) * 2 ;
	data->player.dirY = sin(data->player.rA) * 2 ;
	if (keycode == 13) // avancer
	{
		if (!checkWall(data, &data->ray, data->player.rA, 0))
		{
			data->player.x += data->player.dirX;
			data->player.y += data->player.dirY;
		}
	}
	if (keycode == 1)
	{
		if (!checkWall(data, &data->ray, data->player.rA, 1))
		{
			data->player.x -= data->player.dirX;
			data->player.y -= data->player.dirY;
		}
	}
	if (keycode == 53)
		exit(0);
	mlx_clear_window(data->mlx, data->win);
	data->img = mlx_new_image(data->mlx, sWidth, sHeight);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
							&data->endian);
	drawSky(data);
	drawGround(data);						
	drawMap(data);
	drawPlayerPos(data, data->player.x, data->player.y);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

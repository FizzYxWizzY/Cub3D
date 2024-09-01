/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:21:02 by mflury            #+#    #+#             */
/*   Updated: 2024/08/31 16:30:01 by mflury           ###   ########.fr       */
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

int cclose()
{
	exit(0);
}

int	main(void)
{
	t_data	img;
	
	createMap(&img);
	img.mlx = mlx_init();
	initPlayerStruct(&img.player);
	img.win = mlx_new_window(img.mlx, sWidth, sHeight, "Hello world!");
	drawScene(&img);
	// mlx_hook(img.win, ON_KEYDOWN, 2, key_hook, &img);
	mlx_key_hook(img.win, key_hook, &img);
	mlx_hook(img.win, ON_DESTROY, 0, cclose, &img); // redcross close
	mlx_loop(img.mlx);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		exit(0);
	rotateView(data, keycode);
	data->player.dirX = cos(data->player.rA) * 2 ; // détermine la direction en x et (* 2) augment la vitesse
	data->player.dirY = sin(data->player.rA) * 2 ; // détermine la direction en y et (* 2) augment la vitesse
	move(data, keycode);
	drawScene(data);
	return (0);
}

void drawScene(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	data->img = mlx_new_image(data->mlx, sWidth, sHeight);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
							&data->endian);					
	raycasting(data);
	minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
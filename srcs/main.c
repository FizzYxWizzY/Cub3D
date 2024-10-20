/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:21:02 by mflury            #+#    #+#             */
/*   Updated: 2024/09/02 00:39:36 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// PARSER:
// 		1. verify map path.
// 		2. init the path of each texture and color.
// 		3. verify that all the texture path are openable and the color are in range (0,255).
// 		4. find the start of the map.
// 		5. measure the map.
// 		6. malloc map size and fill it with ' '.
//		7. copy map from file to the array (with a border of 1 all around the map).
// 
// 






// void	init_player(t_player *p, t_file *file)
// {
// 	p->x = get_start_x(map, file);
// 	p->y = get_start_y(map, file);
// }

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
	file->textures.trgb_floor = 0;
	file->textures.ceiling[0] = -1;
	file->textures.ceiling[1] = -1;
	file->textures.ceiling[2] = -1;
	file->textures.trgb_ceiling = 0;
	file->map = NULL;
	file->maplinecount = 0;
	file->maxlength = 0;
}

// I MUST NOT DO THE SO_LONG SHIT AGAIN!!!!!!!!!!!!!!!!!! (lies)

void	free_all(t_file *file)
{
	int	i;

	i = 0;
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
	if (!file->map)
		return;
	while (i < (file->maplinecount + 2))
		free(file->map[i++]);
	free(file->map);
}

// Yay! parsing is almost done! :D  ...and i still have to do render shit T_T ARTHUUUUUUR WHY T_T

int	main(int argc, char **argv)
{
	t_file	file;
	t_mlx	mlx;
	// t_player player;

	parse_file(argc, argv, &file);
	set_trgb_all(&file);
	// init_player(&player);
	create_window(&mlx, &file);
	draw_background(&mlx, &file);
	// draw_minimap(&mlx, &file);
	// draw_bg(&mlx);
	// TO BE DELETED
	// printf("texture north: %s\n", file.textures.north);
	// printf("texture south: %s\n", file.textures.south);
	// printf("texture east: %s\n", file.textures.east);
	// printf("texture west: %s\n", file.textures.west);
	// printf("texture floor: [%d,%d,%d]\n", file.textures.floor[0], file.textures.floor[1], file.textures.floor[2]);
	// printf("texture ceiling: [%d,%d,%d]\n",  file.textures.ceiling[0], file.textures.ceiling[1], file.textures.ceiling[2]);
	// printf("texture count: %d\n", file.textures.count);
	//
	mlx_do_key_autorepeaton(mlx.mlx);
	mlx_hook(mlx.mlx_win, ON_KEYDOWN, (1L<<0), keeb_listener, &file);
	mlx_loop(mlx.mlx);
	mlx_clear_window(mlx.mlx, mlx.mlx_win);
	// mlx_destroy_image(mlx.mlx, mlx.mlx_win);
	// mlx_destroy_window(mlx.mlx, mlx.mlx_win);
	free_all(&file);
	return EXIT_SUCCESS;
}

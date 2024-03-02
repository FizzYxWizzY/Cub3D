/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:21:02 by mflury            #+#    #+#             */
/*   Updated: 2024/03/02 22:39:10 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_file	*file;
	
	if (argc > 2)
		error("too much arguments.");
	if (argc < 2)
		error("need the map path as argument.");
	if (path_check(argv[1]) != 0)
		error("map path is trash.");

	
	return EXIT_SUCCESS;
}

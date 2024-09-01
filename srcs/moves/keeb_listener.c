/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keeb_listener.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 03:49:42 by mflury            #+#    #+#             */
/*   Updated: 2024/09/01 13:55:44 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	keeb_listener(int keycode, t_mlx *mlx, t_file *file)
{
	(void) file;
	(void) mlx;
	printf("\nkeycode = %d\n", keycode);
	if (keycode == KEY_ESC)
	{
		// mlx_loop_end(mlx->mlx);
		exit (0);
	}
	// else if (keycode == KEY_W)
	// 	move_up(player, file, mlx);
	// else if (keycode == KEY_A)
	// 	move_left(player, file, mlx);
	// else if (keycode == KEY_S)
	// 	move_down(player, file, mlx);
	// else if (keycode == KEY_D)
	// 	move_right(player, file, mlx);
	return (0);
}
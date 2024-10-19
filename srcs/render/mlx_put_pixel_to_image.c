/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_pixel_to_image.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 01:27:12 by mflury            #+#    #+#             */
/*   Updated: 2024/09/09 16:58:09 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


// PK TU MARCHE PAS FDP ,bhjkjfhgc fkljh; b
// 
// social NE = 600/mois
// social VS = 1200/mois
// ...
// tout quitter pour aller boire des bieres a la gare d yverdon avec raoul.
//
// T_T T_T T_T T_T T_T T_T T_T T_T T_T T_T T_T T_T T_T T_T T_T T_T T_T

void	mlx_put_pixel_to_image(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

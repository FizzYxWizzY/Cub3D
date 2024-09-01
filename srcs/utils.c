/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:35:58 by mflury            #+#    #+#             */
/*   Updated: 2024/08/31 14:36:11 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int copyIntTbl(t_map *map, int tbl[24][24])
{
	int	x;
	int	y;

	x = 0;
	map->worldMap = malloc(sizeof(int *) * (map->mapHeight));
	if (!map->worldMap)
		return (0);
	while(x < map->mapHeight)
	{
		map->worldMap[x] = malloc(sizeof(int) * (map->mapWidth));
		if (!map->worldMap[x])
			return (0);
		x++;
	}
	if (!tbl)
		return (0);
	x = 0;
	y = 0;
	while (y < map->mapHeight)
	{
		while (x < map->mapWidth)
		{
			
	map->worldMap[y][x] = tbl[y][x];
			x++;
		}
		x = 0;
		y++;
	}
	return (1);
}

double checkAngle(double angle)
{
	if (angle < 0)
    	angle += 2 * M_PI;
	if (angle > 2 * M_PI)
    	angle -= 2 * M_PI;
	return angle;
}

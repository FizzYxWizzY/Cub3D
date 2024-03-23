/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:41:32 by abourgue          #+#    #+#             */
/*   Updated: 2024/03/23 15:25:42 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int createMap(t_data *data)
{
	int worldMap[24][24] = 
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	if (!initMapStruct(&data->map))
		return (0);
	if (!copyIntTbl(&data->map, worldMap))
		return (0);
	return (1);
}

void	minimap(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	drawBottom(data);
	drawPlayerPos(data, data->player.x, data->player.y);
	drawRaysMiniMap(data);
	while (++y < data->map.mapWidth)
	{
		while (++x < data->map.mapHeight)
		{
			if (data->map.worldMap[y][x] == 1)
				drawSquare(data, data->map.x, data->map.y);
			data->map.x += data->map.sizeWall;
		}
		data->map.y += data->map.sizeWall;
		data->map.x = 0;
		x = -1;
	}
	data->map.y = 0;
}

void	drawRaysMiniMap(t_data *data)
{
	double  x;
	double  angle;

	angle = checkAngle(data->player.rA - DR * 45);
	x = 0;
	while (x < sWidth)
	{
	    rayDist(data, &data->ray, angle);
        drawLine(data, data->ray.nextX, data->ray.nextY, 0xAA00FF);
		angle += 90 * DR / sWidth;
		checkAngle(angle);
		x += 1;
	}
}

void	drawBottom(t_data *data)
{
	int x;
	int y;
	
	x = -1;
	y = -1;
	while (++y < data->map.mapHeight * data->map.sizeWall)
	{
		while (++x < data->map.mapHeight * data->map.sizeWall)
			my_mlx_pixel_put(data, x, y, 0x000000);
		x = -1;
	}	
}

void	drawSquare(t_data *data, int x, int y)
{
	int xDraw = -1;
	int yDraw = -1;
	while (++yDraw <= data->map.sizeWall)
	{
		while (++xDraw <= data->map.sizeWall)
			my_mlx_pixel_put(data, x + xDraw, y + yDraw, 0x00FF0000);
		xDraw = -1;
	}
}
#include "../cub3d.h"

int drawMap(t_data *data)
{
	int	x;
	int	y;
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
	x = -1;
	y = -1;
	if (!initMapStruct(&data->map))
		return (0);
	if (!copyIntTbl(&data->map, worldMap))
		return (0);
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
	return (1);
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

void	drawRays(t_data *data)
{
	double angle;
	double angleEnd;
	double temp;
	int	x;
	angle = data->player.rA + M_PI / 4; // définis l'angle de base a -45
	angleEnd = data->player.rA - M_PI / 4; // définis l'angle de base a +45 (tot 90)
	data->player.rI = 0;
	x = 0;
	while (angle >= angleEnd)
	{
		x += 1;
		printf("%f\n", data->player.rA);
		raycast(data, &data->ray, angle, 0xAA00FF);
		temp = angle * 100 - 0.1;
		angle = temp / 100;
		data->player.rI += screenWidth / 1571;
	}
	printf("%d\n\n", x);
}
#include "../cub3d.h"


// void	drawRays(t_data *data)
// {
// 	double angle;
// 	double angleEnd;
// 	double temp;
// 	int	x;

// 	angle = data->player.rA + M_PI / 4; // définis l'angle de base a -45
// 	angleEnd = data->player.rA - M_PI / 4; // définis l'angle de base a +45 (tot 90)
// 	data->player.rI = 0;
// 	x = 0;
// 	while (angle >= angleEnd)
// 	{
// 		x += 1;
// 		raycast(data, &data->ray, angle, 0xAA00FF);
// 		temp = angle * 100 - 0.1;
// 		angle = temp / 100;
// 		data->player.rI += sWidth / 1571;
// 	}
// 	printf("%f\n", data->player.rA);
// 	printf("%d\n", x);
// }

void	drawRays(t_data *data)
{
	double	x;
	double angle;

	angle = checkAngle(data->player.rA - DR * 45);
	x = 0;
	data->player.rI = sWidth;
	while (x < sWidth)
	{
		
		raycast(data, &data->ray, angle, 0xAA00FF);
		angle += 90 * DR / sWidth;
		checkAngle(angle);
		data->player.rI += 1 ; // position x du rayon
		x += 1;
	}
}

void	drawSky(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < sHeight / 2)
	{
		while (++x < sWidth)
			my_mlx_pixel_put(data, x, y, 0x77B5FE);
		x = -1;
	}
}

void	drawGround(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	y = sHeight / 2 - 1;
	while (++y < sHeight)
	{
		while (++x < sWidth)
			my_mlx_pixel_put(data, x, y, 0xADFF2F);
		x = -1;
	}
}
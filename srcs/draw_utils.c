#include "../cub3d.h"

void	drawLine(t_data *data,int x2,int y2, int color)
{
	double	steps;
	double	x;
	double	y;
	int		i;

	data->player.dX = x2 - data->player.x;
	data->player.dY = y2 - data->player.y;
	if (abs(data->player.dX) > abs(data->player.dY))
		steps = abs(data->player.dX);
	else
		steps = abs(data->player.dY);
	data->player.incrX = data->player.dX / steps;
	data->player.incrY = data->player.dY / steps;
	x = data->player.x;
	y = data->player.y;
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(data, x, y, color);
		x += data->player.incrX;
		y += data->player.incrY;
		i++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
#include "../cub3d.h"

void	drawPlayerPos(t_data *data, int x, int y)
{
	my_mlx_pixel_put(data, x , y, 0x00FF00);
	my_mlx_pixel_put(data, x + 1 , y, 0x00FF00);
	my_mlx_pixel_put(data, x , y + 1, 0x00FF00);
	my_mlx_pixel_put(data, x + 1 , y + 1, 0x00FF00);
}
#include "../cub3d.h"

void	drawPlayerPos(t_data *data, int x, int y)
{
	my_mlx_pixel_put(data, x , y, 0x00FF00);
	my_mlx_pixel_put(data, x + 1 , y, 0x00FF00);
	my_mlx_pixel_put(data, x , y + 1, 0x00FF00);
	my_mlx_pixel_put(data, x + 1 , y + 1, 0x00FF00);
	drawPlayerDirection(data);
}

void	drawPlayerDirection(t_data *data)
{
	// raycast(data, &data->ray, data->player.rA, 0xFF0000);
	drawRays(data);
	// drawFOV(data);
}

void	drawFOV(t_data *data)
{
	double angle;
	

	angle = data->player.rA + M_PI / 4; // fov droite
	printf("%f\n", angle * 100);
	raycast(data, &data->ray, angle, 0xFF8000);
	angle = data->player.rA - M_PI / 4; // fov gauche
	raycast(data, &data->ray, angle, 0xAA00FF);
}

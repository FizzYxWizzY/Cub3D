#include "../cub3d.h"

void rotateView(t_data *data, int keycode)
{
	if (keycode == 2)
	{
		data->player.rA += 0.1; // tourner
		if (data->player.rA > 2 * M_PI)
			data->player.rA -= 2 * M_PI;
	}
	else if (keycode == 0)
	{
		data->player.rA -= 0.1;
		if (data->player.rA < 0)
			data->player.rA += 2 * M_PI;
	}
}

void	move(t_data *data, int keycode)
{
	if (keycode == 13) // avancer
	{
		if (!checkWall(data, &data->ray, data->player.rA, 0))
		{
			data->player.x += data->player.dirX;
			data->player.y += data->player.dirY;
		}
	}
	if (keycode == 1) // reculer
	{
		if (!checkWall(data, &data->ray, data->player.rA, 1))
		{
			data->player.x -= data->player.dirX;
			data->player.y -= data->player.dirY;
		}
	}
}

int	checkWall(t_data *data, t_raycast *ray, double angle, int dir)
{
	double nextX;
	double nextY;
    // Réinitialisez les coordonnées du rayon et l'angle du joueur
    initRaycastStruct(ray, data, angle);
	if (dir == 1)
	{
		nextX = ray->interX - ray->dirX;
		nextY = ray->interY - ray->dirY;
	}
	else
	{
		nextX = ray->interX + ray->dirX;
		nextY = ray->interY + ray->dirY;
	}
    ray->mapX = nextX / data->map.sizeWall;
    ray->mapY = nextY / data->map.sizeWall;
    ray->interX = nextX;
    ray->interY = nextY;
    if (ray->mapX >= 0 && ray->mapX < data->map.mapWidth &&
           ray->mapY >= 0 && ray->mapY < data->map.mapHeight &&
           data->map.worldMap[ray->mapY][ray->mapX] != 1)
		return (0);
	return (1);
}


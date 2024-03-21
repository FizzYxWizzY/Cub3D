#include "../cub3d.h"

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



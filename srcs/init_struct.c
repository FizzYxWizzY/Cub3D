#include "../cub3d.h"



int	initRaycastStruct(t_raycast *ray, t_data *data, double angle)
{
	ray->dirX = cos(angle);
	ray->dirY = sin(angle);
	ray->posX = data->player.x;
	ray->posY = data->player.y;
	ray->interX = ray->posX;
	ray->interY = ray->posY;
	ray->mapX = ((ray->posX - data->map.x) / data->map.sizeWall);
	ray->mapY = ((ray->posY - data->map.y) / data->map.sizeWall);
	if (ray->dirX >= 0)
		ray->stepX = 1;
	else
		ray->stepX = -1;
	if (ray->dirY >= 0)
		ray->stepY = 1;
	else
		ray->stepY = -1;
	return (1);
}

int	initMapStruct(t_map *map)
{
	map->mapWidth = 24;
	map->mapHeight = 24;
	map->sizeWall = 12;
	map->x = 0;
	map->y = 0;
	return (1);
}

int	initPlayerStruct(t_player *player)
{
	player->x = 75;
	player->y = 75;
	player->dirX = 0;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.66;
	player->rA = 0;
	player->rI = 0;
	player->dX = 0;
	player->dY = 0;
	player->incrX = 0;
	player->incrY = 0;
	return (1);
}

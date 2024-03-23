#include "../cub3d.h"

void	raycasting(t_data *data)
{
	double  x;
	double  angle;
    double  dist;

    drawSky(data);
	drawGround(data);
	angle = checkAngle(data->player.rA - DR * 45); // set l'angle a -45 pour le premier rayon
	x = 0;
	data->player.rI = sWidth;
	while (x < sWidth)
	{
		dist = rayDist(data, &data->ray, angle); // calcul la distance du rayon
        drawWalls(data, dist, angle); // déssine le mur
        data->player.rI += 1 ; // position x du rayon
		angle += 90 * DR / sWidth;
		checkAngle(angle);
		x += 1;
	}
}

double  rayDist(t_data *data, t_raycast *ray, double angle)
{
    double diffX;
    double diffY;
    // Réinitialisez les coordonnées du rayon et l'angle du joueur
    initRaycastStruct(ray, data, angle);
    // Bouclez pour trouver l'intersection avec le mur
    while (data->map.worldMap[ray->mapY][ray->mapX] != 1)
    {
        ray->nextX = ray->interX + ray->dirX;
        ray->nextY = ray->interY + ray->dirY;
        ray->mapX = ray->nextX / data->map.sizeWall;
        ray->mapY = ray->nextY / data->map.sizeWall;
        ray->interX = ray->nextX;
        ray->interY = ray->nextY;
    }
    diffX = ray->nextX - data->player.x;
    diffY = ray->nextY - data->player.y;
    return (sqrt(pow(diffX, 2) + pow(diffY, 2)));
}

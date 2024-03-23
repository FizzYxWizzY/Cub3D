#include "../cub3d.h"

void raycast(t_data *data, t_raycast *ray, double angle, int color)
{
	double nextX;
	double nextY;
    double diffX;
    double diffY;
    double dist; // distance entre le joueur et le point d impact
    double lineH; // la hauteur a affiché du mur 
    double lineO; // décalage pour afficher depuis le sol (visuellement )
    int y;
    // Réinitialisez les coordonnées du rayon et l'angle du joueur
    initRaycastStruct(ray, data, angle);
    
    // Bouclez pour trouver l'intersection avec le mur
    while (data->map.worldMap[ray->mapY][ray->mapX] != 1)
    {
        nextX = ray->interX + ray->dirX;
        nextY = ray->interY + ray->dirY;
        ray->mapX = nextX / data->map.sizeWall;
        ray->mapY = nextY / data->map.sizeWall;
        ray->interX = nextX;
        ray->interY = nextY;
    }
    diffX = nextX - data->player.x;
    diffY = nextY - data->player.y;
    dist = sqrt(pow(diffX, 2) + pow(diffY, 2));
    angle = checkAngle(data->player.rA - angle);
    lineH = (data->map.sizeWall * sHeight) / (dist * cos(angle)); // taille du mur a dessiner
	if (lineH > sHeight)
		lineH = sHeight;
	lineO = sHeight / 2 - lineH / 2;
    y = 0;
    while (y < lineH)
    {
        my_mlx_pixel_put(data, data->player.rI, y + lineO, 0xAA00FF);
        y += 1;
    }
    drawLine(data, nextX, nextY, color);
}

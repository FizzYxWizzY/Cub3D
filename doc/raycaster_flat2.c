/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:56:57 by mflury            #+#    #+#             */
/*   Updated: 2024/10/19 07:47:45 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_data(t_file *file)
{
	file->fd = -1;
	file->mappath = NULL;
	file->textures.count = 0;
	file->textures.north = NULL;
	file->textures.south = NULL;
	file->textures.west = NULL;
	file->textures.east = NULL;
	file->textures.floor[0] = -1;
	file->textures.floor[1] = -1;
	file->textures.floor[2] = -1;
	file->textures.trgb_floor = 0;
	file->textures.ceiling[0] = -1;
	file->textures.ceiling[1] = -1;
	file->textures.ceiling[2] = -1;
	file->textures.trgb_ceiling = 0;
	file->map = NULL;
	file->maplinecount = 0;
	file->maxlength = 0;
}

// I MUST NOT DO THE SO_LONG SHIT AGAIN!!!!!!!!!!!!!!!!!! (lies)

void	free_all(t_file *file)
{
	int	i;

	i = 0;
	if (file->textures.north)
		free(file->textures.north);
	if (file->textures.south)
		free(file->textures.south);
	if (file->textures.east)
		free(file->textures.east);
	if (file->textures.west)
		free(file->textures.west);
	if (file->mappath)
		free(file->mappath);
	if (!file->map)
		return;
	while (i < (file->maplinecount + 2))
		free(file->map[i++]);
	free(file->map);
}

void	mlx_put_pixel_to_image(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_column_to_img(t_mlx *mlx, int x, int drawStart, int drawEnd, int color)
{
	while (drawStart < drawEnd)
		mlx_put_pixel_to_image(mlx, x, drawStart++, color);
}

// LOOKING NORTH:
// dirXY	-1;0
// planeXY	0;0.666

// LOOKING SOUTH:
// dirXY
// planeXY

// LOOKING WEST:
// dirXY	0;-1
// planeXY	-0.666;0

// LOOKING EAST:
// dirXY	0;1
// planeXY	0.666;0 

void	pov_side(char mapcell, t_structptr *s)
{
	if (mapcell == 'N')
		rotate(s, 2 * pi);
	else if (mapcell == 'S')
		rotate(s, pi);
	else if (mapcell == 'W')
		rotate(s, pi / 2);
	else if (mapcell == 'E')
		rotate(s, -pi / 2);
}

void  init_casting_base(t_casting *casting, t_file *file, t_structptr *s)
{
	casting->posX = 0.5 + get_start_y(file->map, file); // 4; // 22 // if == 1 -> +0.5 // if == 23 -> -0.5
	casting->posY = 0.5 + get_start_x(file->map, file); // 8; // 12 // if == 1 -> +0.5 // if == 23 -> -0.5
	casting->dirX = -1;
	casting->dirY = 0;
	casting->planeX = 0;
	casting->planeY = 0.666;
	pov_side(file->map[(int)casting->posX][(int)casting->posY], s);
}

void  init_casting_loop_part_one(t_casting *casting)
{
	casting->cameraX = 2 * casting->x / (double)screenWidth - 1;
	casting->rayDirX = casting->dirX + casting->planeX * casting->cameraX;
	casting->rayDirY = casting->dirY + casting->planeY * casting->cameraX;
	casting->mapX = (int)casting->posX;
	casting->mapY = (int)casting->posY;
	
	if (casting->rayDirX == 0)
		casting->deltaDistX = 1e30;
	else
		casting->deltaDistX = fabs(1 / casting->rayDirX);
	if (casting->rayDirY == 0)
		casting->deltaDistY = 1e30;
	else
		casting->deltaDistY = fabs(1 / casting->rayDirY);
}

void  init_casting_loop(t_casting *casting)
{
	init_casting_loop_part_one(casting);
	casting->hit = 0;
	if(casting->rayDirX < 0)
	{
		casting->stepX = -1;
		casting->sideDistX = (casting->posX - casting->mapX) * casting->deltaDistX;
	}
	else
	{
		casting->stepX = 1;
		casting->sideDistX = (casting->mapX + 1.0 - casting->posX) * casting->deltaDistX;
	}
	if(casting->rayDirY < 0)
	{
		casting->stepY = -1;
		casting->sideDistY = (casting->posY - casting->mapY) * casting->deltaDistY;
	}
	else
	{
		casting->stepY = 1;
		casting->sideDistY = (casting->mapY + 1.0 - casting->posY) * casting->deltaDistY;
	}
}

void  dda(t_casting *r, char **worldMap)
{
	while(r->hit == 0)
	{
		if(r->sideDistX < r->sideDistY)
		{
    		r->sideDistX += r->deltaDistX;
    		r->mapX += r->stepX;
    		r->side = 0;
    	}
    	else
    	{
      		r->sideDistY += r->deltaDistY;
      		r->mapY += r->stepY;
      		r->side = 1;
    	}
    	if(worldMap[r->mapX][r->mapY] == '1')
			r->hit = 1;
  	}
}

void  calc_dist(t_casting *r)
{
	if(r->side == 0)
		r->perpWallDist = (r->sideDistX - r->deltaDistX);
	else
		r->perpWallDist = (r->sideDistY - r->deltaDistY);
	r->lineHeight = (int)(screenHeight / r->perpWallDist);
	r->drawStart = -r->lineHeight / 2 + screenHeight / 2;
	if(r->drawStart < 0)
		r->drawStart = 0;
	r->drawEnd = r->lineHeight / 2 + screenHeight / 2;
	if(r->drawEnd >= screenHeight)
		r->drawEnd = screenHeight;
}

// void	calc_dist(t_casting *r)
// {
// 	if(r->side == 0)
// 		r->perpWallDist = (r->sideDistX - r->deltaDistX);
// 	else
// 		r->perpWallDist = (r->sideDistY - r->deltaDistY);
// 	r->lineHeight = (int)(screenHeight / r->perpWallDist);

// 	if (r->lineHeight == INT_MIN)
// 	{
// 		if (screenHeight / 2 > INT_MAX - INT_MAX)
// 			r->drawStart = INT_MAX;
// 		else
// 			r->drawEnd = INT_MAX / 2 + screenHeight;
// 	}
// 	else
// 	{
// 		r->drawStart = -r->lineHeight / 2 + screenHeight / 2;
// 	}
// 	if (r->drawStart < 0)
// 		r->drawStart = 0;
// 	r->drawEnd = r->lineHeight / 2 + screenHeight / 2;
// 	if (r->drawEnd >= screenHeight)
// 		r->drawEnd = screenHeight - 1;
// }


void  init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, screenWidth, screenHeight, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
}

void	draw_background(t_mlx *mlx, int ceiling, int floor)
{
	int	y;
	size_t	x;

	y = 0;
	x = 0;
	while (y < screenHeight)
	{
			while (x < screenWidth)
			{
				if (y < (screenHeight / 2))
					mlx_put_pixel_to_image(mlx, x++, y, ceiling);
				else
					mlx_put_pixel_to_image(mlx, x++, y, floor);
			}
			x = 0;
			++y;
	}
}

int	mlx_get_pixel_from_image(t_img *img, int x, int y)
{
	char	*src;

	if (!img || !img->addr)
	{
		ft_putstr_fd("Image is NULL\n", 2);
		return (-1);
	}
	if (x < 0 || y >= img->img_width || y < 0 || y >= img->img_height)
	{
		ft_putstr_fd("Coordinates are out of bounds\n", 2);
		return (-1);
	}
	src = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)src);
}

void	choose_texture(t_structptr *s, int texX, int texY)
{
		if(s->r->side == 1 && s->r->rayDirY < 0) // WEST WALL
			s->r->color = mlx_get_pixel_from_image(s->img[3], texX, texY);
		else if(s->r->side == 1 && s->r->rayDirY > 0) // EAST WALL
			s->r->color = mlx_get_pixel_from_image(s->img[2], texX, texY);
		else if (s->r->side == 0 && s->r->rayDirX < 0) // NORTH WALL
			s->r->color = mlx_get_pixel_from_image(s->img[0], texX, texY);
		else if (s->r->side == 0 && s->r->rayDirX > 0) // SOUTH	WALL
			s->r->color = mlx_get_pixel_from_image(s->img[1], texX, texY);
}

void	calc_tex(t_structptr *s)
{
	int texX;
	int texY;
	double step;
	double texPos;
	int y;

    texX = (int)(s->r->wallX * (double)64);
    if(s->r->side == 0 && s->r->rayDirX > 0)
		texX = 64 - texX - 1;
    if(s->r->side == 1 && s->r->rayDirY < 0)
		texX = 64 - texX - 1;
    step = 1.0 * 64 / s->r->lineHeight;
    texPos = (s->r->drawStart - screenHeight / 2 + s->r->lineHeight / 2) * step;
    y = s->r->drawStart;
	while (y < s->r->drawEnd)
    {
       	texY = (int)texPos & (64 - 1);
       	texPos += step;
		choose_texture(s, texX, texY);
		mlx_put_pixel_to_image(s->mlx, s->r->x, y, s->r->color);
		++y;
   	}
}

int  frame_maker(t_structptr *s)
{
	mlx_destroy_image(s->mlx->mlx, s->mlx->img);
	s->mlx->img =  mlx_new_image(s->mlx->mlx, screenWidth, screenHeight);
	s->mlx->addr = mlx_get_data_addr(s->mlx->img, &s->mlx->bits_per_pixel, &s->mlx->line_length, &s->mlx->endian);
	draw_background(s->mlx, s->file->textures.trgb_ceiling, s->file->textures.trgb_floor);
	s->r->x = 0;
	while (s->r->x < screenWidth)
	{
		init_casting_loop(s->r);
		dda(s->r, s->file->map);
		calc_dist(s->r);
    	if (s->r->side == 0)
			s->r->wallX = s->r->posY + s->r->perpWallDist * s->r->rayDirY;
    	else
			s->r->wallX = s->r->posX + s->r->perpWallDist * s->r->rayDirX;
    	s->r->wallX -= floor((s->r->wallX));
		calc_tex(s);
		s->r->x++;
	}
	mlx_clear_window(s->mlx->mlx, s->mlx->mlx_win);
	mlx_put_image_to_window(s->mlx->mlx, s->mlx->mlx_win, s->mlx->img, 0, 0);
	return (0);
}

void	move(t_structptr *s, double dx, double dy)
{
	if (s->file->map[(int)(s->r->posX + dx + 0.01)][(int)(s->r->posY + dy + 0.01)] != '1' &&
		s->file->map[(int)(s->r->posX + dx + 0.01)][(int)(s->r->posY + dy + 0.01)] != ' ')
	{
		s->r->posX += dx;
		s->r->posY += dy;
	}
}

void	rotate(t_structptr *s, double alpha)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = s->r->dirX;
    s->r->dirX = s->r->dirX * cos(alpha) - s->r->dirY * sin(alpha);
    s->r->dirY = oldDirX * sin(alpha) + s->r->dirY * cos(alpha);
    oldPlaneX = s->r->planeX;
    s->r->planeX = s->r->planeX * cos(alpha) - s->r->planeY * sin(alpha);
    s->r->planeY = oldPlaneX * sin(alpha) + s->r->planeY * cos(alpha);
}

int cclose(t_structptr *s)
{
	mlx_clear_window(s->mlx->mlx, s->mlx->mlx_win);
	mlx_destroy_image(s->mlx->mlx, s->mlx->img);
	mlx_destroy_window(s->mlx->mlx, s->mlx->mlx_win);
	mlx_destroy_display(s->mlx->mlx);
	free(s->mlx->mlx);
	free_all(s->file);
	exit(0);
}

int keeb_listener(int keycode, t_structptr *s)
{
	if (keycode == KEY_ESC)
		cclose(s);
	else if (keycode == KEY_W)
		move(s, s->r->dirX * 0.5, s->r->dirY * 0.5);
	else if (keycode == KEY_S)
		move(s, s->r->dirX * (-0.5), s->r->dirY * (-0.5));
	else if (keycode == KEY_A)
		move(s, s->r->dirY * (-0.5), s->r->dirX * 0.5);
	else if (keycode == KEY_D)
		move(s, s->r->dirY * (0.5), s->r->dirX * (-0.5));
	else if (keycode == KEY_LEFT)
		rotate(s, 0.5);
	else if (keycode == KEY_RIGHT)
		rotate(s, -0.5);
	return 0;
}

void	set_texture_to_image(t_structptr *s)
{
	s->img[0] = malloc(sizeof(t_img));
	s->img[0]->texture = mlx_xpm_file_to_image(s->mlx->mlx, s->file->textures.north, &s->img[0]->img_width, &s->img[0]->img_height);
	s->img[0]->addr = mlx_get_data_addr(s->img[0]->texture, &s->img[0]->bits_per_pixel, &s->img[0]->line_length, &s->img[0]->endian);
	
	s->img[1] = malloc(sizeof(t_img));
	s->img[1]->texture = mlx_xpm_file_to_image(s->mlx->mlx, s->file->textures.south, &s->img[1]->img_width, &s->img[1]->img_height);
	s->img[1]->addr = mlx_get_data_addr(s->img[1]->texture, &s->img[1]->bits_per_pixel, &s->img[1]->line_length, &s->img[1]->endian);

	s->img[2] = malloc(sizeof(t_img));
	s->img[2]->texture = mlx_xpm_file_to_image(s->mlx->mlx, s->file->textures.east, &s->img[2]->img_width, &s->img[2]->img_height);
	s->img[2]->addr = mlx_get_data_addr(s->img[2]->texture, &s->img[2]->bits_per_pixel, &s->img[2]->line_length, &s->img[2]->endian);

	s->img[3] = malloc(sizeof(t_img));
	s->img[3]->texture = mlx_xpm_file_to_image(s->mlx->mlx, s->file->textures.west, &s->img[3]->img_width, &s->img[3]->img_height);
	s->img[3]->addr = mlx_get_data_addr(s->img[3]->texture, &s->img[3]->bits_per_pixel, &s->img[3]->line_length, &s->img[3]->endian);
}

int main(int argc, char **argv)
{
	t_file		file;
	t_mlx		mlx;
	t_casting	r;
	t_structptr	s;
	
	s.file = &file;
	s.mlx = &mlx;
	s.r = &r;
	parse_file(argc, argv, &file);
	set_trgb_all(&file);
 	init_mlx(&mlx);
	set_texture_to_image(&s); // still need free img managemeent
	init_casting_base(&r, &file, &s);
  	frame_maker(&s);
  	mlx_loop_hook(mlx.mlx, frame_maker, &s);
	mlx_hook(mlx.mlx_win, ON_KEYDOWN, (1L<<0), keeb_listener, &s);
 	mlx_hook(mlx.mlx_win, ON_DESTROY, 0, cclose, &s);
	mlx_loop(mlx.mlx);
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:56:57 by mflury            #+#    #+#             */
/*   Updated: 2024/09/07 03:37:07 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

enum e_keys
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
};

enum e_events
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

int worldMap[mapHeight][mapWidth]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct s_mlx
{
	void		*img;
	char		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void		*mlx;
	void		*mlx_win;
	int		img_width;
	int		img_height;
}			t_mlx;

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

typedef struct s_casting	t_casting;

struct s_casting
{
	double  posX;
	double  posY;
	double  dirX;
	double  dirY;
	double  planeX;
	double  planeY;
	int     x;
	double  cameraX;
	double  rayDirX;
	double  rayDirY;
	int     mapX;
	int     mapY;
	double  sideDistX;
	double  sideDistY;
	double  deltaDistX;
	double  deltaDistY;
	double  perpWallDist;
	int     stepX;
	int     stepY;
	int     hit;
	int     side;
	int     lineHeight;
	int     drawStart;
	int     drawEnd;
	int     color;
};

void  init_casting_base(t_casting *casting)
{
	casting->posX = 22;
	casting->posY = 12;
	casting->dirX = -1;
	casting->dirY = 0;
	casting->planeX = 0;
	casting->planeY = 0.666;
}

void  init_casting_loop(t_casting *casting)
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

void  dda(t_casting *r, int worldMap[mapHeight][mapWidth])
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
    if(worldMap[r->mapX][r->mapY] > 0)
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

void  init_mlx(t_mlx *mlx)
{
  mlx->mlx = mlx_init();
  mlx->mlx_win = mlx_new_window(mlx->mlx, screenWidth, screenHeight, "Cub3D");
  mlx->img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
  mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
}

void	draw_background(t_mlx *mlx)
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
					mlx_put_pixel_to_image(mlx, x++, y, 0x0004D6FF);
				else
					mlx_put_pixel_to_image(mlx, x++, y, 0x0000D40E);
			}
			x = 0;
			++y;
	}
}

typedef struct s_structptr
{
	t_mlx     *mlx;
	t_casting *r;
}				t_structptr;

int  frame_maker(t_structptr *s/*, int worldMap[mapHeight][mapWidth]*/)
{
	mlx_destroy_image(s->mlx->mlx, s->mlx->img);
	s->mlx->img =  mlx_new_image(s->mlx->mlx, screenWidth, screenHeight);
	s->mlx->addr = mlx_get_data_addr(s->mlx->img, &s->mlx->bits_per_pixel, &s->mlx->line_length, &s->mlx->endian);
	draw_background(s->mlx);
	s->r->x = 0;
	while (s->r->x < screenWidth)
	{
		init_casting_loop(s->r);
		dda(s->r, worldMap);
		calc_dist(s->r);
		if(s->r->side == 1)
			s->r->color = 0x000000ff;
		else
			s->r->color = 0x00ff0000;
		draw_column_to_img(s->mlx, s->r->x, s->r->drawStart, s->r->drawEnd, s->r->color);
		s->r->x++;
	}
	mlx_clear_window(s->mlx->mlx, s->mlx->mlx_win);
	mlx_put_image_to_window(s->mlx->mlx, s->mlx->mlx_win, s->mlx->img, 0, 0);
	return (0);
}

void	move(t_structptr *s, double dx, double dy)
{
	if (worldMap[(int)(s->r->posX + dx)][(int)(s->r->posY + dy)] == 0)
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
	// mlx_loop_end(s->mlx->mlx);
	mlx_clear_window(s->mlx->mlx, s->mlx->mlx_win);
	mlx_destroy_image(s->mlx->mlx, s->mlx->img);
	mlx_destroy_window(s->mlx->mlx, s->mlx->mlx_win);
	mlx_destroy_display(s->mlx->mlx);
	free(s->mlx->mlx);
	// mlx_loop_end(s->mlx->mlx);
	exit(0);
	// return 0;
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


int main(/*int argc, char **argv*/)
{
  t_mlx     mlx;
  t_casting r;
  t_structptr s;

  s.mlx = &mlx;
  s.r = &r;
  // ctx.map = worldMap;


 	init_mlx(&mlx);
  	init_casting_base(&r);
  	frame_maker(&s); // (s->mlx->mlx, s->r, worldMap);
  // frame_maker(&mlx, &r, worldMap);
  // frame_maker(&mlx, &r, worldMap);
 	// mlx_do_key_autorepeaton(mlx.mlx);
  	mlx_loop_hook(mlx.mlx, frame_maker, &s);
	mlx_hook(mlx.mlx_win, ON_KEYDOWN, (1L<<0), keeb_listener, &s);
 	mlx_hook(mlx.mlx_win, ON_DESTROY, 0, cclose, &s);
	mlx_loop(mlx.mlx);

  // while(1)
  // {
  //   r.x = 0;
  //   while (r.x < screenWidth)
  //   {
  //     init_casting_loop(&r);
  //     dda(&r, worldMap);
  //     calc_dist(&r);
  //     if(r.side == 1)
  //       r.color = 0x000000ff;
  //     else
  //       r.color = 0x00ff0000;
  //     draw_column_to_img(&mlx, r.x, r.drawStart, r.drawEnd, r.color);
  //     ++r.x;
  //   }
  //   mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0, 0);
  // }
}

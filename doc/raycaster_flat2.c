/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:56:57 by mflury            #+#    #+#             */
/*   Updated: 2024/09/05 14:34:34 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

//place the example code below here:

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
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx;
	void		*mlx_win;
	int			img_width;
	int			img_height;
}				t_mlx;



void	mlx_put_pixel_to_image(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void  draw_column_to_img(t_mlx *mlx, int x, int drawStart, int drawEnd, int color)
{
  
  while (drawStart < drawEnd)
    mlx_put_pixel_to_image(mlx, x, drawStart++, color);
}

typedef struct s_casting
{
	double  posX; // = 22;
  double  posY; // = 12;  //x and y start position
  double  dirX; // = -1;
  double  dirY; // = 0; //initial direction vector
  double  planeX; // = 0;
  double  planeY; // = 0.666; //the 2d raycaster version of camera plane

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
}				t_casting;

void  init_casting_base(t_casting *r)
{
  r->posX = 22;
  r->posY = 12;
  r->dirX = -1;
  r->dirY = 0; //initial direction vector
  r->planeX = 0;
  r->planeY = 0.666;
}

void  init_casting_loop(t_casting *r)
{
  //calculate ray position and direction
  r->cameraX = 2 * r->x / (double)screenWidth - 1; //x-coordinate in camera space
  r->rayDirX = r->dirX + r->planeX * r->cameraX;
  r->rayDirY = r->dirY + r->planeY * r->cameraX;
  //which box of the map we're in
  r->mapX = (int)r->posX;
  r->mapY = (int)r->posY;

  if (r->rayDirX == 0)
    r->deltaDistX = 1e30;
  else
    r->deltaDistX = fabs(1 / r->rayDirX);
  if (r->rayDirY == 0)
    r->deltaDistY = 1e30;
  else
    r->deltaDistY = fabs(1 / r->rayDirY);
  
  r->hit = 0;
  if(r->rayDirX < 0)
  {
    r->stepX = -1;
    r->sideDistX = (r->posX - r->mapX) * r->deltaDistX;
  }
  else
  {
    r->stepX = 1;
    r->sideDistX = (r->mapX + 1.0 - r->posX) * r->deltaDistX;
  }
  if(r->rayDirY < 0)
  {
    r->stepY = -1;
    r->sideDistY = (r->posY - r->mapY) * r->deltaDistY;
  }
  else
  {
    r->stepY = 1;
    r->sideDistY = (r->mapY + 1.0 - r->posY) * r->deltaDistY;
  }
}

void  dda(t_casting *r, int worldMap[mapHeight][mapWidth])
{
  while(r->hit == 0)
  {
    //jump to next map square, either in x-direction, or in y-direction
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
    //Check if ray has hit a wall
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

  //Calculate height of line to draw on screen
  r->lineHeight = (int)(screenHeight / r->perpWallDist);

  //calculate lowest and highest pixel to fill in current stripe
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
	int		y;
	size_t	x;

	y = 0;
	x = 0;
	while (y < screenHeight)
	{
			while (x < screenWidth)
			{
				if (y < (screenHeight / 2))
					mlx_put_pixel_to_image(mlx, x++, y, 0x0004D6FF); // ceiling bg
				else
					mlx_put_pixel_to_image(mlx, x++, y, 0x0000D40E); // floor bg
			}
			x = 0;
			++y;
	
	}
}

typedef struct s_structptr
{
	t_mlx     *mlx;
  t_casting *r;
  // int       *map[24];

}				t_structptr;

int  frame_maker(t_structptr *s/*, int worldMap[mapHeight][mapWidth]*/)
{
  printf("HI!\n");
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
    ++s->r->x;
  }
  mlx_clear_window(s->mlx->mlx, s->mlx->mlx_win);
  mlx_put_image_to_window(s->mlx->mlx, s->mlx->mlx_win, s->mlx->img, 0, 0);
  return 0;
}

void  move_w(t_structptr *s)
{
  printf("hi! LOL\n");
  // (void)s;
  if(worldMap[(int)(s->r->posX + s->r->dirX * 0.5)][(int)s->r->posY] == 0)
    s->r->posX += s->r->dirX * 0.5;
  if(worldMap[(int)(s->r->posX)][(int)(s->r->posY + s->r->dirY * 0.5)] == 0)
    s->r->posY += s->r->dirY * 0.5;
  // mlx_clear_window(mlx->mlx, mlx->mlx_win);
  // mlx_destroy_image(mlx->mlx, mlx->img);
  // mlx->img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
  // mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
  // frame_maker(s/*, worldMap*/);
}

void  move_s(t_structptr *s)
{
  printf("hi! LOL\n");
  // (void)s;
  if(worldMap[(int)(s->r->posX - s->r->dirX * 0.5)][(int)s->r->posY] == 0)
    s->r->posX -= s->r->dirX * 0.5;
  if(worldMap[(int)s->r->posX][(int)(s->r->posY - s->r->dirY * 0.5)] == 0)
    s->r->posY -= s->r->dirY * 0.5;
  // mlx_clear_window(mlx->mlx, mlx->mlx_win);
  // mlx_destroy_image(mlx->mlx, mlx->img);
  // mlx->img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
  // mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
  // frame_maker(s/*, worldMap*/);
}

void  move_a(t_structptr *s)
{
  printf("hi! LOL\n");
  // (void)s;
  if(worldMap[(int)(s->r->posX - s->r->dirX * 0.5)][(int)s->r->posY] == 0)
    s->r->posX += s->r->dirY * 0.5; //  s->r->dirX * 1
  if(worldMap[(int)s->r->posX][(int)(s->r->posY - s->r->dirY * 0.5)] == 0)
    s->r->posY += s->r->dirX * 0.5; // s->r->dirY * 1
  // mlx_clear_window(mlx->mlx, mlx->mlx_win);
  // mlx_destroy_image(mlx->mlx, mlx->img);
  // mlx->img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
  // mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
  // frame_maker(s/*, worldMap*/);
}

void  move_d(t_structptr *s)
{
  printf("hi! LOL\n");
  // (void)s;
  if(worldMap[(int)(s->r->posX - s->r->dirX * 1)][(int)s->r->posY] == 0)
    s->r->posX -= s->r->dirY * 0.5; //  s->r->dirX * 1
  if(worldMap[(int)s->r->posX][(int)(s->r->posY - s->r->dirY * 1)] == 0)
    s->r->posY -= s->r->dirX * 0.5; // s->r->dirY * 1
  // mlx_clear_window(mlx->mlx, mlx->mlx_win);
  // mlx_destroy_image(mlx->mlx, mlx->img);
  // mlx->img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
  // mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
  // frame_maker(s/*, worldMap*/);
}

void  move_left(t_structptr *s)
{
  printf("hi! LOL\n");
  // (void)s;
  if(worldMap[(int)(s->r->posX - s->r->dirX * 0.5)][(int)s->r->posY] == 0)
    s->r->posX -= s->r->dirY * 0.5; //  s->r->dirX * 1
  if(worldMap[(int)s->r->posX][(int)(s->r->posY - s->r->dirY * 0.5)] == 0)
    s->r->posY -= s->r->dirX * 0.5; // s->r->dirY * 1
  // mlx_clear_window(mlx->mlx, mlx->mlx_win);
  // mlx_destroy_image(mlx->mlx, mlx->img);
  // mlx->img = mlx_new_image(mlx->mlx, screenWidth, screenHeight);
  // mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
  // frame_maker(s/*, worldMap*/);
}

void  move_right(t_structptr *s)
{
  double oldDirX;
  double oldPlaneX;

  oldDirX = s->r->dirX;
  s->r->dirX = s->r->dirX * cos(-0.5) - s->r->dirY * sin(-0.5);
  s->r->dirY = oldDirX * sin(-0.5) + s->r->dirY * cos(-0.5);
  oldPlaneX = s->r->planeX;
  s->r->planeX = s->r->planeX * cos(-0.5) - s->r->planeY * sin(-0.5);
  s->r->planeY = oldPlaneX * sin(-0.5) + s->r->planeY * cos(-0.5);
}

int cclose()
{
  exit(0);
}

int keeb_listener(int keycode, t_structptr *s)
{
  // (void) s;

  if (keycode == KEY_ESC)
    cclose();
  else if (keycode == KEY_W)
    move_w(s);
  else if (keycode == KEY_A)
    move_a(s);
  else if (keycode == KEY_S)
    move_s(s);
  else if (keycode == KEY_D)
    move_d(s);
  else if (keycode == KEY_LEFT)
    move_left(s);
  else if (keycode == KEY_RIGHT)
    move_right(s);
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
  mlx_do_key_autorepeaton(mlx.mlx);
  mlx_loop_hook(mlx.mlx, frame_maker, &s);
	mlx_hook(mlx.mlx_win, ON_KEYDOWN, (1L<<0), keeb_listener, &s);
  mlx_hook(mlx.mlx_win, ON_DESTROY, 0, &cclose, &s);
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

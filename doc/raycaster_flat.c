/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:00:43 by mflury            #+#    #+#             */
/*   Updated: 2024/09/03 14:41:56 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// COMPILE:
// gcc -Wall -Werror -Wextra -L../minilibx/linux -lmlx -lXext -lX11 -lm -lbsd raycaster_flat.c

// #include "../../cub3d.h"
#include "../minilibx/linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>

int worldMap[24][24]=
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

  printf("x= %d\n", x);

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void  draw_column_to_img(t_mlx *mlx, int x, int drawStart, int drawEnd, int color)
{
  
  while (drawStart < drawEnd)
    mlx_put_pixel_to_image(mlx, x, drawStart++, color);
}

int main()
{
  double  posX;
  double  posY;  //x and y start position
  
  double  dirX;
  double  dirY; //initial direction vector
  
  double planeX;
  double planeY;
  
  int w;
  int x;
  
  double cameraX;
  double rayDirX;
  double rayDirY;
  
  int mapX;
  int mapY;
  
  double sideDistX;
  double sideDistY;
  
  double deltaDistX;
  double deltaDistY;
  
  double perpWallDist;
  
  int stepX;
  int stepY;
  
  int hit;
  int side;
  
  int lineHeight;
  
  int h;
  
  int drawStart;
  int drawEnd;
  
  int color;
  
  // int finish; // trying to replace done()

  t_mlx mlx;


  posX = 22;
  posY = 12;
  dirX = -1;
  dirY = 0;
  planeX = 0;
  planeY = 0.66;
  w = 640; // GUESS: screenWidth
  x = 0;
  hit = 0;
  h = 480; // GUESS: screenHigth
  // finish = 0;

  // screen(w, h, 0, "CUB3D");
  mlx.mlx = mlx_init();
  mlx.mlx_win = mlx_new_window(mlx.mlx, w, h, "Cub3D");
  mlx.img = mlx_new_image(mlx.mlx, w, h);
  mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
  // the gameloop starts, this is the loop that draws a whole frame and reads the input every time.
  // while(!finish)
  // {
    // int i = 0;
    while (x < w)
    {
      //calculate ray position and direction
      cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
      rayDirX = dirX + planeX * cameraX;
      rayDirY = dirY + planeY * cameraX;
      //which box of the map we're in
      mapX = (int)posX;
      mapY = (int)posY;
      // drawStart = 0;
      // drawEnd = 0;
      // lineHeight = 0;
      // perpWallDist = 0;
      //length of ray from current position to next x or y-side

      // deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
      if (rayDirX == 0)
        deltaDistX = 1e30;
      else
        deltaDistX = fabs(1 / rayDirX);
      // deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
      if (rayDirY == 0)
        deltaDistY = 1e30;
      else
        deltaDistY = fabs(1 / rayDirY);
      
      //what direction to step in x or y-direction (either +1 or -1)

      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }

      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(worldMap[mapX][mapY] > 0)
          hit = 1;
      }
      if(side == 0)
        perpWallDist = (sideDistX - deltaDistX);
      else
        perpWallDist = (sideDistY - deltaDistY);

      //Calculate height of line to draw on screen
      lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
     // // if (lineHeight == INT_MIN)
     // // {
     // //   if (h / 2 > INT_MAX - INT_MAX)
     // //     drawStart = INT_MAX;
     // //   else
     // //     drawStart = INT_MAX + h / 2;
     // // }
     // // else
     // // {
     // //   drawStart = -lineHeight / 2 + h / 2;
     // // }

      drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)
        drawStart = 0;
      drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h)
        drawEnd = h - 1;
      printf("drawStart= %d\n", drawStart);
      //choose wall color
      // switch(worldMap[mapX][mapY])
      // {
      //   case 1:  color = 0x00ff0000;  break; //red
      //   case 2:  color = 0x0000ff00;  break; //green
      //   case 3:  color = 0x000000ff;   break; //blue
      //   case 4:  color = 0x00ffffff;  break; //white
      //   default: color = 0x00000000; break; //black
      // }
      // if (worldMap[mapX][mapY] == 1)
      color = 0x00ff0000;
      // else if (worldMap[mapX][mapY] == 2)
      //   color = 0x0000ff00;
      // else if (worldMap[mapX][mapY] == 3)
      //   color = 0x000000ff;
      // else if (worldMap[mapX][mapY] == 4)
      //   color = 0x00ffffff;
      // else
      //   color = 0x00000000;

      //give x and y sides different brightness
      // if(side == 1)
      //   color = color / 2;
      
      //draw the pixels of the stripe as a vertical line
      // verLine(x, drawStart, drawEnd, color); DRAW SINGLE COLUMN
      draw_column_to_img(&mlx, x, drawStart, drawEnd, color); // (t_ray should have "x, drawStart, drawEnd")
      
      // printf("loop count= %d\n", i++);
      x++;
    }
    // finish = 1;
    mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0, 0);
    // printf("x value: %d, w value: %d\n", x, w);
    // printf("1e30= %f\n", 1e30);
  // }
  sleep(5);
}













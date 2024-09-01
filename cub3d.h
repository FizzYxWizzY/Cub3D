/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:21:41 by mflury            #+#    #+#             */
/*   Updated: 2024/08/31 16:19:02 by mflury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include "./libft/libft.h"
#include "./gnl/get_next_line.h"
# ifdef __APPLE__

#include "./minilibx/macOS/mlx.h"
# else

#include "./minilibx/linux/mlx.h"

# endif

# ifdef __APPLE__
enum e_keys
{
	KEY_ESC = 53,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
};

enum e_events
{
	ON_KEYDOWN = 0,
	ON_KEYUP = 0,
	ON_MOUSEDOWN = 0,
	ON_MOUSEUP = 0,
	ON_MOUSEMOVE = 0,
	ON_EXPOSE = 0,
	ON_DESTROY = 0
};
# else
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
# endif

#define sWidth 1366
#define sHeight 768
#define DR 0.0174533
#define M_PI 3.14159265358979323846

typedef struct	s_textures
{
	int			count;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	int			floor[3];
	int			ceiling[3];
}				t_textures;

typedef struct	s_file
{
	int			fd;
	t_textures	textures;
	char		**map;
}				t_file;

typedef struct	s_map {
	int	x;
	int	y;
	int	mapWidth;
	int sizeWall;
	int	mapHeight;
	int	**worldMap;
}				t_map;

typedef struct	s_player {
	double		x;
	double		y;
	double		dirX;
	double		dirY;
	double		rA;
	double		rI;
	double		planeX;
	double		planeY;
	double		incrX; //draw
	double		incrY; //draw
	int			dX; //draw
	int			dY; //draw
}				t_player;

typedef struct	s_raycast {
	double		interX;
	double		interY;
	double		dirX;
	double		dirY;
	double		posX;
	double		posY;
	double		stepX;
	double		stepY;
	double		nextX;
	double		nextY;
	int			mapX;	//coorrdonée du joueur dans la map
	int			mapY;	//*
	
}				t_raycast;

typedef struct	s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		map;
	t_player	player;
	t_raycast	ray;
}				t_data;

void	error(char *msg);
void	init_data(t_file *file);
int		path_check(char *map_path);
void	line_check(char *line, t_file *file);
void	set_colors(int *tab, char *line);
void	set_path(char *path, char *line);

//-------------------draw_map.c-------------------
void	drawWalls(t_data *data, double dist, double angle);
void	drawSky(t_data *data);
void	drawGround(t_data *data);

//-------------------draw_minimap.c-------------------
int 	createMap(t_data *data);
void	minimap(t_data *data);
void	drawBottom(t_data *data);
void 	drawSquare(t_data *data, int x, int y);
void	drawRaysMiniMap(t_data *data);

//-------------------draw_player.c-------------------
void 	drawPlayerPos(t_data *data, int x, int y);

//-------------------draw_utils.c-------------------
void	drawLine(t_data *data,int x2,int y2, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

//-------------------init_struct.c-------------------
int		initRaycastStruct(t_raycast *ray, t_data *data, double angle);
int		initMapStruct(t_map *map);
int		initPlayerStruct(t_player *player);

//-------------------main.c-------------------
int		key_hook(int keycode, t_data *data);
void 	drawScene(t_data *data);

//-------------------move.c-------------------
void 	rotateView(t_data *data, int keycode);
void	move(t_data *data, int keycode);
int		checkWall(t_data *data, t_raycast *ray, double angle, int dir);

//-------------------raycasting.c-------------------
void	raycasting(t_data *data);
double	rayDist(t_data *data, t_raycast *ray, double angle);

//-------------------utils.c-------------------
int		copyIntTbl(t_map *map, int tbl[24][24]);
double	checkAngle(double angle);






#endif

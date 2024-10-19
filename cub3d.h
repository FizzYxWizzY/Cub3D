/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:21:41 by mflury            #+#    #+#             */
/*   Updated: 2024/10/18 00:09:48 by mflury           ###   ########.fr       */
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
#include "./minilibx/linux/mlx.h"

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

#define screenWidth 1280
#define screenHeight 720
#define mapWidth 24
#define mapHeight 24
#define pi 3.14159265359

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

typedef struct	s_textures
{
	int			count;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	int			floor[3];
	int			trgb_floor;
	int			ceiling[3];
	int			trgb_ceiling;
}				t_textures;

typedef struct	s_img
{
	void		*texture;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			img_width;
	int			img_height;
}				t_img;

typedef struct	s_file
{
	int			fd;
	char		*mappath;
	t_textures	textures;
	char		**map;
	int			maplinecount;
	size_t		maxlength;
}				t_file;

typedef struct	s_casting
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	int			x;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	int			color;
	double		wallX;
}				t_casting;

typedef struct	s_structptr
{
	t_mlx		*mlx;
	t_casting	*r;
	t_file		*file;
	t_img		*img[5];
}				t_structptr;

// General Utils:

void	error(char *msg);
void	free_all(t_file *file);

// Parsing: 

void	parse_file(int argc,char **argv,t_file *file);

	// Texture & Colors:

void	init_data(t_file *file);
void	check_args(int argc, char **argv, t_file *file);
int		path_check(char *map_path);
void	set_textures(t_file *file);
void	line_check(char *line, t_file *file);
char	*set_path(char *line);
void	set_colors(int *tab, char *line);
void	verify_paths(t_file *file);

	// Map:

void	set_map(t_file *file);
void	set_map_size(t_file *file);
int		is_map_start(char *line);
void	fill_map(t_file *file);
int		is_valid_char_only(t_file *file);
void	start_count(t_file *file);
void	is_closed_map(t_file *file);
char	**copy_map(t_file *file);
size_t	get_start_x(char **map, t_file *file);
int		get_start_y(char **map, t_file *file);
int		floodfill(char **map, t_file *file, size_t x, int y);
void	free_copy(char **map, t_file *file);

// Moves:

int		keeb_listener(int keycode, t_structptr *s);
void	move(t_structptr *s, double dx, double dy);
void	rotate(t_structptr *s, double alpha);

// Render:

void	mlx_put_pixel_to_image(t_mlx *mlx, int x, int y, int color);
int		create_trgb(int r, int g, int b);
void	set_trgb_all(t_file *file);

int		frame_maker(t_structptr *s);
void	draw_background(t_mlx *mlx, int ceiling, int floor);
void	init_casting_loop(t_casting *casting);
void	init_casting_loop_part_one(t_casting *casting);
void	dda(t_casting *casting, char **worldMap);
void	calc_dist(t_casting *casting);
void	draw_column_to_img(t_mlx *mlx, int x, int drawStart, int drawEnd, int color);


#endif
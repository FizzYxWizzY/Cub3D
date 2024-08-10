/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflury <mflury@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 06:21:41 by mflury            #+#    #+#             */
/*   Updated: 2024/08/10 04:54:13 by mflury           ###   ########.fr       */
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
	char		*mappath;
	t_textures	textures;
	char		**map;
	int			maplinecount;
	int			maxlength;
}				t_file;

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

#endif

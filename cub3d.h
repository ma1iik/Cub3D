/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 02:27:49 by ma1iik            #+#    #+#             */
/*   Updated: 2023/02/06 04:39:46 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CUB3D_H
# define CUB3D_H
# include "mlx.h"
# include <stdlib.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <float.h>
# include <stdio.h>
# include <math.h>

# define WRONG 0
# define RIGHT 1
# define WIDTH 1920
# define HEIGHT 1080
# define TX_L 40

# ifdef __APPLE__
#  define ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define ARROW_L 123
#  define ARROW_R 124
# elif __linux__
#  define ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define ARROW_L 65361 
#  define ARROW_R 65363 
# endif

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct	s_vec {
	int		x;
	int		y;
	float	rad;
}				t_vec;

typedef struct	s_ray {
	float		x;
	float		y;
	int		distance;
}				t_ray;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_data
{
	char	player;
	int		pl_x;
	int		pl_y;
	int		pl_tx_x;
	int		pl_tx_y;
	float	pdx;
	float	pdy;
	float	pa;
	int		map_h;
	int		map_l;
	char	**map;
	char	**map_star;
	void	*mlx;
	void	*win;
	t_img	img;
	t_ray	ray;
}				t_data;

//PARSING
int		ft_parsing(int ac, t_data *data, char *file);
int		ft_check_ext(t_data *data, char *file);
int		ft_error(int n);
int		ft_mapsize(char *file);
int		ft_wrongchar(t_data *data);
int		ft_map_len(t_data *data);
int		ft_fill_map(t_data *data, int fd);
int		ft_fill_map2(t_data *data);
int		ft_fill_map3(t_data *data);
int		ft_checkways(int x, int y, char **map, t_data *data);
int		ft_checkways1(int x, int y, char **map, t_data *data);
int		ft_checkwalls(t_data *data);
int		ft_checkwalls1(t_data *data, char **maps);
int		ft_first_last_row(t_data *data, char **map);
int		ft_rowsbetween(t_data *data, char **map);

//INIT and DRAW
void 	init_draw(t_data *data);
void 	draw_char(char **map, int rows, int cols, t_data *data);
void	draw_circle(t_data *data, int rad, int x, int y, int color);
void 	draw_map(char **map, int rows, int cols, t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_direction(t_data *data, char player);
void	draw_ray(t_data *data, int x0, int y0, int x1, int y1, int color);
void	dda(t_data *data, float x2, float y2, int color);
void 	get_point_at_distance(float player_x, float player_y, float direction, t_data *data);
void ray_till_wall(t_data *data);

//UTILS
int		ft_ischar(char c);
int		ft_isspace(int c);
int		ft_exit(void);
//
int	ft_release(int key);
int	ft_action(int key, t_data *data);

#endif
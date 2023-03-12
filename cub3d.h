/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 02:27:49 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/11 20:02:41 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
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
# define TX_L 64
# define MOVE 2.5
# define FOV 1.0472

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

typedef struct s_vec {
	int		x;
	int		y;
	double	rad;
}				t_vec;

typedef struct s_txt
{
	int		*addr;
	void	*no;
	void	*so;
	void	*ea;
	void	*we;
	int		*a_no;
	int		*a_so;
	int		*a_ea;
	int		*a_we;
	int		*a_fnl;
	int		bpp;
	int		line_length;
	int		size_line;
	int		endian;
	int		img_w;
	int		img_h;
	char	*no_fn;
	char	*ea_fn;
	char	*we_fn;
	char	*so_fn;
	int		type;
	int		l_i;
	int		no_n;
	int		ea_n;
	int		we_n;
	int		so_n;
	int		f_n;
	int		c_n;
	int		no_bpp;
	int		no_l;
	int		no_end;
	int		so_bpp;
	int		so_l;
	int		so_end;
	int		ea_bpp;
	int		ea_l;
	int		ea_end;
	int		we_bpp;
	int		we_l;
	int		we_end;
	int		txt_x;
	int		txt_y;
}	t_txt;

typedef struct s_ray {
	double	ay;
	double	ax;
	double	by;
	double	bx;
	double	x_fnl;
	double	y_fnl;
	double	distance;
	double	plane;
	double	wall_h;
}				t_ray;

typedef struct s_img {
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
	double	pl_tx_x;
	double	pl_tx_y;
	double	x_fnl;
	double	y_fnl;
	double	pa;
	int		map_h;
	int		map_l;
	int		m_fl;
	int		m_ll;
	char	**map;
	char	**map_star;
	void	*mlx;
	void	*win;
	t_img	img;
	t_ray	ray[WIDTH];
	t_txt	texture;
	double	r_distance;
	int		w_vertical;
	double	f_r;
	double	f_g;
	double	f_b;
	double	c_r;
	double	c_g;
	double	c_b;
}				t_data;

//PARSING
int		ft_parsing(int ac, t_data *data, char *file);
int		ft_check_ext(t_data *data, char *file);
int		ft_error(int n);
int		ft_mapsize(char *file);
int		ft_wrongchar(t_data *data);
int		ft_map_len(t_data *data);
int		ft_fill_map(t_data *data, char *file);
int		ft_fill_map2(t_data *data);
int		ft_fill_map3(t_data *data);
int		ft_checkways(int x, int y, char **map, t_data *data);
int		ft_checkways1(int x, int y, char **map, t_data *data);
int		ft_checkwalls(t_data *data);
int		ft_checkwalls1(t_data *data, char **maps);
int		ft_first_last_row(t_data *data, char **map);
int		ft_rowsbetween(t_data *data, char **map);

//INIT and DRAW
void	init_draw(t_data *data);
void	draw_char(char **map, int rows, int cols, t_data *data);
void	draw_circle(t_data *data, int rad, int x, int y, int color);
void	draw_map(char **map, int rows, int cols, t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_direction(t_data *data, char player);
void	draw_ray(t_data *data, int x0, int y0, int x1, int y1, int color);
void	dda(t_data *data, double x2, double y2, int color);
t_ray	ray_till_wall_h(t_data *data, double pa);
t_ray	ray_till_wall_v(t_data *data, double pa);
void	cast_rays1(t_data *data);
double	ft_cor_dis(t_data *data, t_ray *ray, double agl, int x);
void	compare_a_b_cordis(t_data *data, t_ray *ray);

//UTILS
int		ft_ischar(char c);
int		ft_isspace(int c);
int		ft_exit(void);
double	calc_dist(double px, double py, double rx, double ry);
int		check_wall_around(t_data *data, int i, int j, int radius);
//
int		ft_release(int key);
int		ft_action(int key, t_data *data);
void	change_pos(t_data *data, int j, int i);

#endif
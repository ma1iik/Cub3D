/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 02:27:49 by ma1iik            #+#    #+#             */
/*   Updated: 2023/01/25 07:38:55 by ma1iik           ###   ########.fr       */
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
# include <math.h>
# include <float.h>
# include <stdio.h>

# define WRONG 0
# define RIGHT 1

typedef struct s_data
{
	int		pl_x;
	int		pl_y;
	int		map_h;
	int		map_l;
	char	**map;
	char	**map_star;
}				t_data;

int ft_parsing(int ac, t_data *data, char *file);
int ft_check_ext(t_data *data, char *file);
int	ft_error(int n);
int	ft_mapsize(char *file);
int	ft_wrongchar(t_data *data);
int	ft_map_len(t_data *data);
int	ft_fill_map(t_data *data, int fd, char **map);
int	ft_fill_map2(t_data *data);
int	ft_fill_map3(t_data *data);
int	ft_checkways(int x, int y, char **map, t_data *data);
int	ft_checkways1(int x, int y, char **map, t_data *data);
int	ft_ischar(char c);
int	ft_checkwalls1(t_data *data, char **maps);
int ft_first_last_row(t_data *data, char **map);
int		ft_isspace(int c);
int	ft_rowsbetween(t_data *data, char **map);

#endif
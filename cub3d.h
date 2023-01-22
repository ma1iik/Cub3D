/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 02:27:49 by ma1iik            #+#    #+#             */
/*   Updated: 2023/01/22 00:13:14 by ma1iik           ###   ########.fr       */
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
	int i;
	char **map;
}				t_data;

int ft_parsing(int ac, t_data *data, char *file);
int ft_check_ext(t_data *data, char *file);
int ft_fill_map(t_data *data, int fd);
int	ft_error(int n);
int	ft_mapsize(char *file);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 03:23:53 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/16 13:39:44 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_exit(t_data *data)
{
	(void)data;
	// int i;

	// i = 0;
	// printf ("freeing\n");	
	// while (data->map[i]){
	// 	free(data->map[i++]);
	// }
	// free (data->map);
	// i = 0;
	// while (data->map_star[i])
	// 	free(data->map_star[i++]);
	// free (data->map_star);
	exit(0);
}

void	change_pos(t_data *data, int j, int i)
{
	int	ii;
	int	jj;

	data->map[(int)data->pl_tx_y / TX_L][(int)data->pl_tx_x / TX_L] = '0';
	data->map[j / TX_L][i / TX_L] = data->player;
	data->pl_x = i / TX_L;
	data->pl_y = j / TX_L;
}

int	check_exist2(t_data *data, t_ray *ray)
{
	int		x;
	int		y;

	x = (int)ray->bx / TX_L;
	y = (int)ray->by / TX_L;
	if ((x >= 0 && x < data->map_l) && (y >= 0 && y < data->map_h))
	{
		if (data->map[y][x] == '0' || ft_ischar(data->map[y][x]))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	check_exist(t_data *data, t_ray *ray, int n)
{
	int		x;
	int		y;

	if (n == 1)
	{
		if (check_exist1(data, ray))
			return (1);
		else
			return (0);
	}
	else if (n == 2)
	{
		if (check_exist2(data, ray))
			return (1);
		else
			return (0);
	}
	return (0);
}

void	ft_wl(t_data *data, double agl)
{
	if (fabs(data->x_fnl - data->pl_tx_x) >= fabs(data->y_fnl - data->pl_tx_y))
		data->wl = fabs(data->pl_tx_x - data->x_fnl) / cos(agl);
	else
		data->wl = fabs(data->pl_tx_y - data->y_fnl) / sin(agl);
	data->wl = data->wl * cos(data->pa - agl);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:34:17 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/15 19:12:43 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	drawchar2(t_data *data, int y, int x)
{
	data->pl_tx_y = y + TX_L / 2;
	data->pl_tx_x = x + TX_L / 2;
	ft_direction(data, data->player);
}

void	draw_char(char **map, int rows, int cols, t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	y = 0;
	i = 0;
	while (i < rows)
	{
		x = 0;
		j = 0;
		while (j < cols)
		{
			if (ft_ischar(map[i][j]))
			{
				data->player = map[i][j];
				drawchar2(data, y, x);
				return ;
			}
			x += TX_L;
			j++;
		}
		y += TX_L;
		i++;
	}
}

double	add_angle(double start_angle, double delta_angle)
{
	double	result;

	result = fmod(start_angle + delta_angle, 2 * M_PI);
	if (result < 0)
	{
		result += 2 * M_PI;
	}
	return (result);
}

int	check_turn(t_data *data, t_ray *ray, int n)
{
	if (n == 1)
	{
		if ((ray->ay / TX_L) > 0 && (ray->ay / TX_L) < data->map_h
			&& (ray->ax / TX_L) > 0 && (ray->ax / TX_L) < data->map_l)
			return (1);
		else
		{
			return (0);
		}
	}
	else if (n == 2)
	{
		if ((ray->by / TX_L) > 0 && (ray->by / TX_L) < data->map_h
			&& (ray->bx / TX_L) > 0 && (ray->bx / TX_L) < data->map_l)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	check_exist1(t_data *data, t_ray *ray)
{
	int		x;
	int		y;

	x = (int)ray->ax / TX_L;
	y = (int)ray->ay / TX_L;
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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:34:17 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/15 17:53:34 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	find_wall_a2(t_data *data, t_ray *ray, double agl, double *ya)
{
	if ((agl > 0 - 0.0001 && agl < 0 + 0.0001)
		|| (agl > 2 * M_PI - 0.0001 && agl < 2 * M_PI + 0.0001))
	{
		ray->ay = data->pl_tx_y;
		ray->ax = data->map_l * TX_L;
		return (1);
	}
	else if (agl > M_PI - 0.0001 && agl < M_PI + 0.0001)
	{
		ray->ax = 0;
		ray->ay = data->pl_tx_y;
		return (1);
	}
	else if (agl <= M_PI && agl >= 0)
	{
		*ya -= TX_L;
		ray->ay = floor(data->pl_tx_y / TX_L) * (TX_L) - 0.00000001;
	}
	else
	{
		*ya = TX_L;
		ray->ay = floor(data->pl_tx_y / TX_L) * (TX_L) + TX_L;
	}
	return (0);
}

void	find_wall_a(t_data *data, t_ray *ray, double agl)
{
	double	ya;
	double	xa;

	ya = 0;
	if (find_wall_a2(data, ray, agl, &ya))
		return ;
	xa = -ya / tan(agl);
	ray->ax = data->pl_tx_x + (data->pl_tx_y - ray->ay) / tan(agl);
	while ((check_turn(data, ray, 1) == 1) && (check_exist(data, ray, 1) == 1))
	{
		ray->ay += ya;
		ray->ax += xa;
		if (ray->ax > TX_L * data->map_l || ray->ax < 0)
		{
			if (ray->ax > TX_L * data->map_l)
				ray->ax = TX_L * data->map_l - 4;
			else if (ray->ax < 0)
					ray->ax = 0;
			return ;
		}
	}
}

int	find_wall_b2(t_data *data, t_ray *ray, double agl, double *xa)
{
	if (agl < 3 * M_PI / 2 + 0.001 && agl > 3 * M_PI / 2 - 0.001)
	{
		ray->by = TX_L * data->map_h;
		ray->bx = data->pl_tx_x;
		return (1);
	}
	else if (agl < M_PI / 2 + 0.001 && agl > M_PI / 2 - 0.001)
	{
		ray->by = 0;
		ray->bx = data->pl_tx_x;
		return (1);
	}
	else if (agl < 3 * M_PI / 2 && agl > M_PI / 2)
	{
		*xa = -TX_L;
		ray->bx = floor((double)data->pl_tx_x / TX_L) * (TX_L) - 0.00000001;
	}
	else
	{
		*xa = TX_L;
		ray->bx = floor((double)data->pl_tx_x / TX_L) * (TX_L) + TX_L;
	}
	return (0);
}

void	find_wall_b(t_data *data, t_ray *ray, double agl)
{
	double	ya;
	double	xa;

	xa = 0;
	ray->bx = 0;
	ray->by = 0;
	if (find_wall_b2(data, ray, agl, &xa))
		return ;
	ya = -xa * tan(agl);
	ray->by = (double)data->pl_tx_y
		+ ((double)data->pl_tx_x - ray->bx) * tan(agl);
	while ((check_turn(data, ray, 2) == 1) && (check_exist(data, ray, 2) == 1))
	{
		ray->by += ya;
		ray->bx += xa;
		if (ray->by > TX_L * data->map_h || ray->by < 0)
		{
			if (ray->by > TX_L * data->map_h)
				ray->by = TX_L * data->map_h - 4;
			else if (ray->by < 0)
					ray->by = 0;
			return ;
		}
	}
}

double	ft_cor_dis(t_data *data, t_ray *ray, double agl, int x)
{
	(void)x;
	find_wall_a(data, ray, agl);
	find_wall_b(data, ray, agl);
	compare_a_b_cordis(data, ray);
	return (ray->distance);
}


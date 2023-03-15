/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:34:17 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/15 17:55:29 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	compare_a_b_cordis(t_data *data, t_ray *ray)
{
	double	a;
	double	b;
	double	cos_b;

	a = sqrtf(pow(data->pl_tx_x - ray->ax, 2)
			+ pow(data->pl_tx_y - ray->ay, 2));
	b = sqrtf(pow(data->pl_tx_x - ray->bx, 2)
			+ pow(data->pl_tx_y - ray->by, 2));
	if (a < b)
	{
		ray->x_fnl = ray->ax;
		ray->y_fnl = ray->ay;
	}
	else
	{
		ray->x_fnl = ray->bx;
		ray->y_fnl = ray->by;
	}
	ray->distance = sqrt((pow(data->pl_tx_x - ray->x_fnl, 2)
				+ pow(data->pl_tx_y - ray->y_fnl, 2)));
}

void	compare_a_b(t_data *data, t_ray *ray, double agl)
{
	double	a;
	double	b;
	double	cos_ang;

	a = sqrtf(pow(data->pl_tx_x - ray->ax, 2)
			+ pow(data->pl_tx_y - ray->ay, 2));
	b = sqrtf(pow(data->pl_tx_x - ray->bx, 2)
			+ pow(data->pl_tx_y - ray->by, 2));
	if (a < b)
	{
		ray->x_fnl = ray->ax;
		ray->y_fnl = ray->ay;
		data->w_vertical = 0;
	}
	else
	{
		ray->x_fnl = ray->bx;
		ray->y_fnl = ray->by;
		data->w_vertical = 1;
	}
	cos_ang = cos(data->pa - agl);
	ray->distance = sqrt((pow(data->pl_tx_x - ray->x_fnl, 2)
				+ pow(data->pl_tx_y - ray->y_fnl, 2)));
	ray->distance = ray->distance * cos_ang;
}

void	draw_wall(t_data *data, t_ray *ray, int x, double agl)
{
	int		wall_top;
	int		wall_bottom;
	int		color;
	int		mirrored_x;
	double	idx;

	wall_top = HEIGHT / 2 - (ray->wall_h / 2);
	wall_bottom = HEIGHT / 2 + ray->wall_h / 2;
	ft_wl(data, agl);
	if (wall_top < 0)
		wall_top = 0;
	while (wall_top < wall_bottom && wall_top < 1080)
	{
		data->texture.txt_y = (1.0 - (double)(wall_bottom - wall_top)
				/ ray->wall_h) * 64.0;
		idx = (double)data->texture.txt_x
			+ (double)data->texture.txt_y * (double)64;
		color = data->texture.a_fnl[(int)idx];
		mirrored_x = WIDTH - x - 1;
		my_mlx_pixel_put(data, mirrored_x, wall_top, color);
		wall_top++;
	}
}

int	rgb_to_code(t_data *data, int j)
{
	if (j == 1)
		return (0 << 24 | (int)data->f_r << 16
			| (int)data->f_g << 8 | (int)data->f_b);
	else
		return (0 << 24 | (int)data->c_r << 16
			| (int)data->c_g << 8 | (int)data->c_b);
	return (0);
}

void draw_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT / 2)
	{
		while (x < WIDTH)
		{
			my_mlx_pixel_put(data, x, y, rgb_to_code(data, 1));
			x++;
		}
		y++;
		x = 0;
	}
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			my_mlx_pixel_put(data, x, y, rgb_to_code(data, 2));
			x++;
		}
		y++;
		x = 0;
	}
}

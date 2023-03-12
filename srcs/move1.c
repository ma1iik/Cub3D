/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:15:21 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/10 17:06:51 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_release(int key)
{
	if (key == ESC)
		exit(0);
	return (0);
}

void	draw_text(t_data *data)
{
	int		y;
	int		x;

	y = data->pl_tx_y;
	while (y < data->pl_tx_y + TX_L)
	{
		x = data->pl_tx_x;
		while (x < data->pl_tx_x + TX_L)
		{
			my_mlx_pixel_put(data, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}	

void	move_up(t_data *data)
{
	float	i;
	float	j;
	double	delta_x;
	double	delta_y;
	double	wl;

	if (fabs(data->x_fnl - data->pl_tx_x) >= fabs(data->y_fnl - data->pl_tx_y))
		wl = fabs(data->pl_tx_x - data->x_fnl);
	else
		wl = fabs(data->pl_tx_y - data->y_fnl);
	delta_x = (data->x_fnl - data->pl_tx_x) / wl;
	delta_y = (data->y_fnl - data->pl_tx_y) / wl;
	i = data->pl_tx_x + (delta_x * MOVE);
	j = data->pl_tx_y + (delta_y * MOVE);
	if (data->r_distance <= (sqrt((pow(data->pl_tx_x - i, 2)
					+ pow(data->pl_tx_y - j, 2)))))
	{
		i = data->x_fnl - (delta_x / 6);
		j = data->y_fnl - delta_y / 6;
	}
	if (check_wall_around(data, i, j, 0) == 0)
	{
		if (data->pl_tx_x / TX_L != i / TX_L || data->pl_tx_y / TX_L != j / TX_L)
			change_pos(data, j, i);
		data->pl_tx_x = i;
		data->pl_tx_y = j;
		cast_rays1(data);
	}
}

void move_down(t_data *data)
{
	int		i;
	int		j;
	double	delta_x;
	double	delta_y;
	double	wl;

	if (fabs(data->x_fnl - data->pl_tx_x) >= fabs(data->y_fnl - data->pl_tx_y))
		wl = fabs(data->pl_tx_x - data->x_fnl);
	else
		wl = fabs(data->pl_tx_y - data->y_fnl);
	delta_x = ((data->pl_tx_x - data->x_fnl) / wl);
	delta_y = ((data->pl_tx_y - data->y_fnl) / wl);
	i = data->pl_tx_x + (delta_x * MOVE);
	j = data->pl_tx_y + (delta_y * MOVE);
	if (check_wall_around(data, i, j, 0) == 0)
	{
		if (data->pl_tx_x / TX_L != i / TX_L
			|| data->pl_tx_y / TX_L != j / TX_L)
			change_pos(data, j, i);
		data->pl_tx_x += delta_x * MOVE;
		data->pl_tx_y += delta_y * MOVE;
		cast_rays1(data);
	}
}

void	move_left(t_data *data)
{
	int		i;
	int		j;
	double	delta_x;
	double	delta_y;
	double	wl;

	if (fabs(data->x_fnl - data->pl_tx_x) >= fabs(data->y_fnl - data->pl_tx_y))
		wl = fabs(data->pl_tx_x - data->x_fnl);
	else
		wl = fabs(data->pl_tx_y - data->y_fnl);
	delta_x = ((data->y_fnl - data->pl_tx_y) / wl);
	delta_y = ((data->pl_tx_x - data->x_fnl) / wl);
	//printf("dlt y [%.2f] dlt x [%.2f]\n", delta_y, delta_x);
	i = data->pl_tx_x + (delta_x * MOVE);
	j = data->pl_tx_y + (delta_y * MOVE);
	if (check_wall_around(data, i, j, 0) == 0)
	{
		if (data->pl_tx_x/TX_L != i/TX_L || data->pl_tx_y/TX_L != j / TX_L)
			change_pos(data, j, i);
		data->pl_tx_x += delta_x * MOVE;
		data->pl_tx_y += delta_y * MOVE;
		//printf("y [%.2f] x [%.2f]\n\n", data->pl_tx_y, data->pl_tx_x);
		cast_rays1(data);
	}
}

int check_wall_around(t_data *data, int i, int j, int radius)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	r_squared;

	start_x = fmax(0, i - radius);
	start_y = fmax(0, j - radius);
	end_x = fmin(WIDTH - 1, i + radius);
	end_y = fmin(HEIGHT - 1, j + radius);
	r_squared = radius * radius;
	for (int x = start_x; x <= end_x; x++) {
		for (int y = start_y; y <= end_y; y++) {
			if (pow(x - i, 2) + pow(y - j, 2) <= r_squared
				&& data->map[y / TX_L][x / TX_L] == '1')
				return (1);
		}
	}
	return (0);
}

void move_right(t_data *data)
{
	int		i;
	int		j;
	double	delta_x;
	double	delta_y;
	double	wl;

	if (fabs(data->x_fnl - data->pl_tx_x) >= fabs(data->y_fnl - data->pl_tx_y))
		wl = fabs(data->pl_tx_x - data->x_fnl);
	else
		wl = fabs(data->pl_tx_y - data->y_fnl);
	delta_x = ((data->pl_tx_y - data->y_fnl) / wl);
	delta_y = ((data->x_fnl - data->pl_tx_x) / wl);
	//printf("dlt y [%.2f] dlt x [%.2f]\n", delta_y, delta_x);
	i = data->pl_tx_x + (delta_x * MOVE);
	j = data->pl_tx_y + (delta_y * MOVE);
	if (check_wall_around(data, i, j, 0) == 0)
	{
		if (data->pl_tx_x / TX_L != i / TX_L
			|| data->pl_tx_y / TX_L != j / TX_L)
			change_pos(data, j, i);
		data->pl_tx_x += delta_x * MOVE;
		data->pl_tx_y += delta_y * MOVE;
		//printf("y [%.2f] x [%.2f]\n\n", data->pl_tx_y, data->pl_tx_x);
		cast_rays1(data);
	}
}

void	move_angle_r(t_data *data)
{
	data->pa -= M_PI / 36;
	if (data->pa < 0)
		data->pa += 2 * M_PI;
	cast_rays1(data);
	return ;
}

void	move_angle_l(t_data *data)
{
	data->pa = fmod(data->pa + M_PI / 36, 2 * M_PI);
	if (data->pa > 2 * M_PI)
		data->pa -= 2 * M_PI;
	cast_rays1(data);
	return ;
}

int	ft_action(int key, t_data *data)
{
	if (key == KEY_W)
		move_up(data);
	else if (key == KEY_S)
		move_down(data);
	else if (key == KEY_A)
		move_left(data);
	else if (key == KEY_D)
		move_right(data);
	else if (key == ARROW_L)
		move_angle_l(data);
	else if (key == ARROW_R)
		move_angle_r(data);
	// for (int i = 0; i < data->map_h; i++)
	//     printf("%s\n", data->map[i]);
	//printf("\n");
	// printf("py[%.2d]px[%.2d]\n", data->pl_tx_y, data->pl_tx_y);
	// printf("y[%d]x[%d]\n", data->pl_y, data->pl_x);
	return (0);
}

void dda(t_data *data, double x2, double y2, int color)
{
	double	dx;
	double	dy;
	double	xinc;
	double	yinc;
	double	steps;
	int	i;

	i = 0;
	dx = data->pl_tx_x - x2;
	dy = data->pl_tx_y - y2;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	xinc = dx / steps;
	yinc = dy / steps;
	while (i < steps)
	{
		my_mlx_pixel_put(data, (int)round(x2), (int)round(y2), color);
		x2 += xinc;
		y2 += yinc;
		i++;
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:15:21 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/15 21:05:52 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_release(int key, t_data *data)
{
	int i;

	i = 0;
	printf ("frei\n");	
	while (data->map[i]){
		free(data->map[i++]);
	}
	free (data->map);
	i = 0;
	while (data->map_star[i])
		free(data->map_star[i++]);
	free (data->map_star);
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

int	check_wall_around(t_data *data, int i, int j, int radius)
{
	(void)data;
	(void)i;
	(void)j;
	(void)radius;
	return (0);
}

double	find_wl(t_data *data)
{
	if (fabs(data->x_fnl - data->pl_tx_x) >= fabs(data->y_fnl - data->pl_tx_y))
		return (fabs(data->pl_tx_x - data->x_fnl));
	else
		return (fabs(data->pl_tx_y - data->y_fnl));
}

void	move_up(t_data *data)
{
	float	i;
	float	j;
	double	delta_x;
	double	delta_y;
	double	wl;

	wl = find_wl(data);
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

void	move_down(t_data *data)
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
	if (data->map[j / TX_L][i / TX_L] == '1')
	{
		return ;
	}
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
	i = data->pl_tx_x + (delta_x * MOVE);
	j = data->pl_tx_y + (delta_y * MOVE);
	if (data->map[j / TX_L][i / TX_L] == '1')
		return ;
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
	i = data->pl_tx_x + (delta_x * MOVE);
	j = data->pl_tx_y + (delta_y * MOVE);
	if (data->map[j / TX_L][i / TX_L] == '1')
		return ;
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
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:15:21 by ma1iik            #+#    #+#             */
/*   Updated: 2023/01/31 19:15:23 by ma1iik           ###   ########.fr       */
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
	while (y < data->pl_tx_y + 20)
	{
		x = data->pl_tx_x;
		while (x < data->pl_tx_x + 20)
		{
			my_mlx_pixel_put(data, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void	move_down(t_data *data)
{
	//printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y - 100) % 20);
	if ((data->pl_tx_y - 100) % 20 == 0 && data->map[data->pl_y + 1][data->pl_x] == '1')
		return ;
	if ((data->pl_tx_x - 50) % 20 != 0 && (data->map[data->pl_y + 1][data->pl_x] == '1' || data->map[data->pl_y + 1][data->pl_x - 1] == '1'))
		return ;
	if ((data->pl_tx_y - 100) % 20 != 0 && data->map[data->pl_y + 1][data->pl_x] == '0')
	{
		data->map[data->pl_y + 1][data->pl_x] = 'N';
		data->map[data->pl_y][data->pl_x] = '0';
		data->pl_y++;
	}
	draw_text(data);
	data->pl_tx_y += 10;
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	//printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y - 100) % 20);
}

void	move_up(t_data *data)
{
	if ((data->pl_tx_y - 100) % 20 == 0 && data->map[data->pl_y - 1][data->pl_x] == '1')
		return ;
	if ((data->pl_tx_y - 100) % 20 == 0 && (data->pl_tx_x - 50) % 20 != 0 && (data->map[data->pl_y - 1][data->pl_x] == '1' || data->map[data->pl_y - 1][data->pl_x - 1] == '1'))
		return ;
	else if ((data->pl_tx_y - 100) % 20 == 0 && data->map[data->pl_y - 1][data->pl_x] == '0')
	{
		data->map[data->pl_y - 1][data->pl_x] = 'N';
		data->map[data->pl_y][data->pl_x] = '0';
		data->pl_y--;
	}
	draw_text(data);
	data->pl_tx_y -= 10;
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	//printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y - 100) % 20);
}

void	move_right(t_data *data)
{
	if ((data->pl_tx_x - 50) % 20 == 0 && data->map[data->pl_y][data->pl_x + 1] == '1')
		return ;
	if ((data->pl_tx_x - 50) % 20 == 0 && (data->pl_tx_y - 100) % 20 != 0 && data->map[data->pl_y + 1][data->pl_x + 1] == '1')
		return ;
	else if ((data->pl_tx_x - 50) % 20 == 0 && data->map[data->pl_y][data->pl_x + 1] == '0')
	{
		data->map[data->pl_y][data->pl_x + 1] = 'N';
		data->map[data->pl_y][data->pl_x] = '0';
		data->pl_x++;
	}
	draw_text(data);
	data->pl_tx_x += 10;
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	//printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y - 100) % 20);
}

void	move_left(t_data *data)
{
	if ((data->pl_tx_x - 50) % 20 == 0 && data->map[data->pl_y][data->pl_x - 1] == '1')
		return ;
	if ((data->pl_tx_y - 100) % 20 != 0 && data->map[data->pl_y + 1][data->pl_x - 1] == '1')
		return ;
	else if ((data->pl_tx_x - 50) % 20 != 0 && data->map[data->pl_y][data->pl_x - 1] == '0')
	{
		data->map[data->pl_y][data->pl_x - 1] = 'N';
		data->map[data->pl_y][data->pl_x] = '0';
		data->pl_x--;
	}
	draw_text(data);
	data->pl_tx_x -= 10;
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
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
	// printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y - 100) % 20);
	// printf("pl x --> %d\npl tx x / 20 --> %d\n\n", data->pl_x, (data->pl_tx_x - 50) % 20);
	return (0);
}
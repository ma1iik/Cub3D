/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:15:21 by ma1iik            #+#    #+#             */
/*   Updated: 2023/02/02 19:54:05 by ma1iik           ###   ########.fr       */
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
	if ((data->pl_tx_y) % 20 == 0 && data->map[data->pl_y + 1][data->pl_x] == '1')
		return ;
	if ((data->pl_tx_x) % 20 != 0 && (data->map[data->pl_y + 1][data->pl_x] == '1' || data->map[data->pl_y + 1][data->pl_x - 1] == '1'))
		return ;
	if ((data->pl_tx_y) % 20 != 0 && data->map[data->pl_y + 1][data->pl_x] == '0')
	{
		data->map[data->pl_y + 1][data->pl_x] = data->player;
		data->map[data->pl_y][data->pl_x] = '0';
		data->pl_y++;
	}
	//draw_text(data);
	draw_map(data->map, data->map_h, data->map_l, data);
	data->pl_tx_y += 10;
	data->dir.y += 10;
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	draw_line_in_direction(data, data->pl_tx_x + 10, data->pl_tx_y + 10, data->pa, 50);
	//draw_line_in_direction(data, data->pl_tx_x, data->pl_tx_y, data->dir.x, data->dir.y, 0xFF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	//printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y - 100) % 20);
}

void	move_up(t_data *data)
{
	if ((data->pl_tx_y) % 20 == 0 && data->map[data->pl_y - 1][data->pl_x] == '1')
		return ;
	if ((data->pl_tx_y) % 20 == 0 && (data->pl_tx_x) % 20 != 0 && (data->map[data->pl_y - 1][data->pl_x] == '1' || data->map[data->pl_y - 1][data->pl_x - 1] == '1'))
		return ;
	else if ((data->pl_tx_y) % 20 == 0 && data->map[data->pl_y - 1][data->pl_x] == '0')
	{
		data->map[data->pl_y - 1][data->pl_x] = data->player;
		data->map[data->pl_y][data->pl_x] = '0';
		data->pl_y--;
	}
	//draw_text(data);
	draw_map(data->map, data->map_h, data->map_l, data);
	data->pl_tx_y -= 10;
	data->dir.y += 10;
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	draw_line_in_direction(data, data->pl_tx_x + 10, data->pl_tx_y + 10, data->pa, 50);
	//draw_line_in_direction(data, data->pl_tx_x, data->pl_tx_y, data->dir.x, data->dir.y, 0xFF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	//printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y) % 20);
}

void	move_right(t_data *data)
{
	if ((data->pl_tx_x) % 20 == 0 && data->map[data->pl_y][data->pl_x + 1] == '1')
		return ;
	if ((data->pl_tx_x) % 20 == 0 && (data->pl_tx_y) % 20 != 0 && data->map[data->pl_y + 1][data->pl_x + 1] == '1')
		return ;
	else if ((data->pl_tx_x) % 20 == 0 && data->map[data->pl_y][data->pl_x + 1] == '0')
	{
		data->map[data->pl_y][data->pl_x + 1] = data->player;
		data->map[data->pl_y][data->pl_x] = '0';
		data->pl_x++;
	}
	//draw_text(data);
	draw_map(data->map, data->map_h, data->map_l, data);
	data->pl_tx_x += 10;
	data->dir.x += 10;
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	//draw_line_in_direction(data, data->pl_tx_x, data->pl_tx_y, data->dir.x, data->dir.y, 0xFF0000);
	draw_line_in_direction(data, data->pl_tx_x + 10, data->pl_tx_y + 10, data->pa, 50);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	//printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y) % 20);
}

void	move_left(t_data *data)
{
	if ((data->pl_tx_x) % 20 == 0 && data->map[data->pl_y][data->pl_x - 1] == '1')
		return ;
	if ((data->pl_tx_y) % 20 != 0 && data->map[data->pl_y + 1][data->pl_x - 1] == '1')
		return ;
	else if ((data->pl_tx_x) % 20 != 0 && data->map[data->pl_y][data->pl_x - 1] == '0')
	{
		data->map[data->pl_y][data->pl_x - 1] = data->player;
		data->map[data->pl_y][data->pl_x] = '0';
		data->pl_x--;
	}
	//draw_text(data);
	draw_map(data->map, data->map_h, data->map_l, data);
	data->pl_tx_x -= 10;
	data->dir.x -= 10;
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	// draw_line_in_direction(data, data->pl_tx_x, data->pl_tx_y, data->dir.x, data->dir.y, 0xFF0000);
	draw_line_in_direction(data, data->pl_tx_x + 10, data->pl_tx_y + 10, data->pa, 50);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	//printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y) % 20);
}

// void	move_angle_l(t_data *data)
// {
// 	data->pa -= -0.1;
// 	if (data->pa < 0)
// 		data->pa += 2 * M_PI;
// 	data->pdx = cos(data->pa) * 5;
// 	data->pdy = sin(data->pa) * 5;
// 	return ;
// }

// void	move_angle_r(t_data *data)
// {
// 	data->pa += -0.1;
// 	if (data->pa > 2 * M_PI)
// 		data->pa -= 2 * M_PI;
// 	data->pdx = cos(data->pa) * 5;
// 	data->pdy = sin(data->pa) * 5;
// 	return ;
// }]

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
	// else if (key == ARROW_L)
	// 	move_angle_l(data);
	// else if (key == ARROW_R)
	// 	move_angle_r(data);
	// printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y - 100) % 20);
	// printf("pl x --> %d\npl tx x / 20 --> %d\n\n", data->pl_x, (data->pl_tx_x - 50) % 20);
	return (0);
}

void draw_line_in_direction(t_data *data, int x0, int y0, float direction, int length)
{
    int x = x0;
    int y = y0;
    int xinc = length * cos(direction);
    int yinc = length * sin(direction);

    while (x != x0 + xinc || y != y0 - yinc)
    {
		//printf("y is %d\ny inc is %d\n", y, yinc);
		my_mlx_pixel_put(data, x, y, 0xF0000);
        //x ++;F
        y--;
    }
}

void dda(t_data *data, float x2, float y2, int color)
{
	float dx;
	float dy;
	//int	m;
	float	xinc;
	float	yinc;
	float steps;
	int	i = 0;

	dx = data->pl_tx_x + 10 - x2;
	dy = data->pl_tx_y + 10 - y2;
	//m = dy / dx;
	if (dx > dy)
		steps = dx;
	else
		steps = dy;
	xinc = dx / steps;
	yinc = dy / steps;
	printf("y inc = %.1f\ndy is%.1f\nsteps is %.1f\n", yinc, dy, steps);
	while (i < steps)
	{
		printf("x2=%d   y2=is %d\n", (int)round(x2), (int)round(y2));
		my_mlx_pixel_put(data, (int)round(x2), (int)round(y2), color);
		x2 += xinc;
		y2 += yinc;
		i++;
	}
	return ;
}
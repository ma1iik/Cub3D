/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:15:21 by ma1iik            #+#    #+#             */
/*   Updated: 2023/02/03 20:09:58 by ma1iik           ###   ########.fr       */
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
	data->ray.y += 10;
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	//draw_line_in_direction(data, data->pl_tx_x + 10, data->pl_tx_y + 10, data->pa, 50);
	//draw_line_in_direction(data, data->pl_tx_x, data->pl_tx_y, data->dir.x, data->dir.y, 0xFF0000);`
	dda(data, data->ray.x, data->ray.y, 0xFF0000);
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
	data->ray.y -= 10;
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	//draw_line_in_direction(data, data->pl_tx_x + 10, data->pl_tx_y + 10, data->pa, 50);
	//draw_line_in_direction(data, data->pl_tx_x, data->pl_tx_y, data->dir.x, data->dir.y, 0xFF0000);
	dda(data, data->ray.x, data->ray.y, 0xFF0000);
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
	data->ray.x += 10;
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	//draw_line_in_direction(data, data->pl_tx_x, data->pl_tx_y, data->dir.x, data->dir.y, 0xFF0000);
	//draw_line_in_direction(data, data->pl_tx_x + 10, data->pl_tx_y + 10, data->pa, 50);
	dda(data, data->ray.x, data->ray.y, 0xFF0000);
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
	data->ray.x -= 10;
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	//draw_line_in_direction(data, data->pl_tx_x + 10, data->pl_tx_y + 10, data->pa, 50);
	dda(data, data->ray.x, data->ray.y, 0xFF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	//printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y) % 20);
}

void	move_angle_l(t_data *data)
{
	data->pa -= 0.1;
	if (data->pa < 0)
		data->pa += 2 * M_PI;
	data->ray.x = data->pl_tx_x + 10 + 50 * cos(data->pa);
	data->ray.y = data->pl_tx_y + 10 + 50 * sin(data->pa);
	printf("x is %.0f  y is %.0f\n", data->ray.x, data->ray.y);
	draw_map(data->map, data->map_h, data->map_l, data);
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	dda(data, data->ray.x, data->ray.y, 0xFF0000);
	//draw_line_in_direction(data, data->pl_tx_x + 10, data->pl_tx_y + 10, data->pa, 50);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return ;
}

void	move_angle_r(t_data *data)
{
	data->pa += 0.1;
	if (data->pa > 2 * M_PI)
		data->pa -= 2 * M_PI;
	data->ray.x = data->pl_tx_x + 10 + 50 * cos(data->pa);
	data->ray.y = data->pl_tx_y + 10 + 50 * sin(data->pa);
	draw_map(data->map, data->map_h, data->map_l, data);
	draw_circle(data, 10, data->pl_tx_x + 10, data->pl_tx_y + 10, 0xFF0000);
	dda(data, data->ray.x, data->ray.y, 0xFF0000);
	//draw_line_in_direction(data, data->pl_tx_x + 10, data->pl_tx_y + 10, data->pa, 50);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);	return ;
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
	// printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y - 100) % 20);
	// printf("pl x --> %d\npl tx x / 20 --> %d\n\n", data->pl_x, (data->pl_tx_x - 50) % 20);
	return (0);
}

void	dda_2(int num, t_data *data, float x1, float xinc, float y2, float yinc, int color)
{
	int		x2;

	x2 = x1;
	if (num == 1)
	{
		while (x2 != x2 - xinc)
		{
			if (xinc < 0)
				my_mlx_pixel_put(data, x2--, y2, color);
			else if ( xinc >= 0)
			{
				printf("LOL\n");
				my_mlx_pixel_put(data, x2++, y2, color);
			}
			
		}
	}
	else if (num == 2)
	{
		while (y2 != y2 + yinc)
		{
			my_mlx_pixel_put(data, x2, y2++, color);
		}
	}
}

void dda(t_data *data, float x2, float y2, int color)
{
    float dx;
    float dy;
    float	xinc;
    float	yinc;
    float steps;
    int	i = 0;

    dx = data->pl_tx_x + 10 - x2;
    dy = data->pl_tx_y + 10 - y2;
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

void draw_line_in_direction(t_data *data, int x0, int y0, float direction, float length)
{
    float x = (float)x0;
    float y = (float)y0;
    float xinc = length * cos(direction);
    float yinc = length * sin(direction);

	// dda(data, )
	// printf("y is %.1f\ny inc is %.1f\n", y, yinc);
    while (x != x0 + xinc || y != y0 - yinc)
    {
		my_mlx_pixel_put(data, x, y, 0xFf0000);
        //x ++;F
        y--;
    }
}

void dda_angle_v(t_data *data, float radian, float length, int color)
{
    float x2 = (data->pl_tx_x + 10) + length * cos(radian);
    float y2 = (data->pl_tx_y + 10) + length * sin(radian);
    float dx = x2 - (data->pl_tx_x + 10);
    float dy = y2 - (data->pl_tx_y + 10);
    float xinc = dx / length;
    float yinc = dy / length;
    int steps = length;
    int i = 0;

    while (i < steps)
    {
        my_mlx_pixel_put(data, (int)round(data->pl_tx_x), (int)round(data->pl_tx_y), color);
        data->pl_tx_x += xinc;
        data->pl_tx_y += yinc;
        i++;
    }
    return;
}
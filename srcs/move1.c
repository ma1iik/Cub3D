/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:15:21 by ma1iik            #+#    #+#             */
/*   Updated: 2023/02/13 16:57:22 by ma1iik           ###   ########.fr       */
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

void move_up(t_data *data)
{
	if ((data->pl_tx_x - TX_L / 2) % TX_L == 0 && ((data->pl_tx_y - TX_L / 2) % TX_L == 0 && data->map[data->pl_y - 1][data->pl_x] == '1'))
	{
		printf("wall next, x grade, exit\n");
		return ;
	}
	else if ((data->pl_tx_y - TX_L / 2) % TX_L == 0 && ((data->pl_tx_x - TX_L/2) % TX_L != 0))
	{
		printf("here\n");
		if (data->pl_tx_x % TX_L < TX_L/2)
		{
			if (data->map[data->pl_y - 1][data->pl_x] == '1' || data->map[data->pl_y - 1][data->pl_x - 1] == '1')
				return;
		}
		else
		{
			if (data->map[data->pl_y - 1][data->pl_x] == '1' || data->map[data->pl_y - 1][data->pl_x + 1] == '1')
				return;
		}
	}
	if ((data->pl_tx_y) % TX_L == 0 && data->map[data->pl_y - 1][data->pl_x] == '0')
	{
		printf("entered moving\n");
		data->map[data->pl_y - 1][data->pl_x] = data->player;
		data->map[data->pl_y][data->pl_x] = '0';
		data->pl_y--;
	}
	//draw_text(data);
	draw_map(data->map, data->map_h, data->map_l, data);
	data->pl_tx_y -= MOVE;
	data->ray.y -= MOVE;
	draw_circle(data, TX_L/2, data->pl_tx_x, data->pl_tx_y, 0xFF0000);
	ray_till_wall(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	//printf("pl y --> %d\npl tx y / TX_L --> %d\n", data->pl_y, (data->pl_tx_y) % 20);
}

void move_down(t_data *data)
{
    if ((data->pl_tx_x - TX_L / 2) % TX_L == 0 && ((data->pl_tx_y - TX_L / 2) % TX_L == 0 && data->map[data->pl_y + 1][data->pl_x] == '1'))
    {
        printf("wall next, x grade, exit\n");
        return ;
    }
    else if ((data->pl_tx_y - TX_L / 2) % TX_L == 0 && ((data->pl_tx_x - TX_L/2) % TX_L != 0))
    {
        if (data->pl_tx_x % TX_L < TX_L/2)
        {
            if (data->map[data->pl_y + 1][data->pl_x] == '1' || data->map[data->pl_y + 1][data->pl_x - 1] == '1')
                return;
        }
        else
        {
            if (data->map[data->pl_y + 1][data->pl_x] == '1' || data->map[data->pl_y + 1][data->pl_x + 1] == '1')
                return;
        }
    }
    if ((data->pl_tx_y) % TX_L == 0 && data->map[data->pl_y + 1][data->pl_x] == '0')
    {
        printf("entered moving\n");
        data->map[data->pl_y + 1][data->pl_x] = data->player;
        data->map[data->pl_y][data->pl_x] = '0';
        data->pl_y++;
    }
    draw_map(data->map, data->map_h, data->map_l, data);
    data->pl_tx_y += MOVE;
    data->ray.y += MOVE;
    draw_circle(data, TX_L/2, data->pl_tx_x, data->pl_tx_y, 0xFF0000);
    ray_till_wall(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void move_right(t_data *data)
{
    if ((data->pl_tx_y - TX_L / 2) % TX_L == 0 && ((data->pl_tx_x - TX_L / 2) % TX_L == 0 && data->map[data->pl_y][data->pl_x + 1] == '1'))
    {
        printf("wall next, y grade, exit\n");
        return ;
    }
    else if ((data->pl_tx_x - TX_L / 2) % TX_L == 0 && ((data->pl_tx_y - TX_L/2) % TX_L != 0))
    {
        if (data->pl_tx_y % TX_L < TX_L/2)
        {
            if (data->map[data->pl_y][data->pl_x + 1] == '1' || data->map[data->pl_y - 1][data->pl_x + 1] == '1')
			{
                return;
			}
        }
        else
        {
            if (data->map[data->pl_y][data->pl_x + 1] == '1' || data->map[data->pl_y + 1][data->pl_x + 1] == '1')
			{
				printf("wtf\n");
                return;
			}
			//here
        }
    }
    if ((data->pl_tx_x) % TX_L == 0 && data->map[data->pl_y][data->pl_x + 1] == '0')
    {
        printf("entered moving\n");
        data->map[data->pl_y][data->pl_x + 1] = data->player;
        data->map[data->pl_y][data->pl_x] = '0';
        data->pl_x++;
    }
    //draw_text(data);
    draw_map(data->map, data->map_h, data->map_l, data);
    data->pl_tx_x += MOVE;
    data->ray.x += MOVE;
    draw_circle(data, TX_L/2, data->pl_tx_x, data->pl_tx_y, 0xFF0000);
    ray_till_wall(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    //printf("pl y --> %d\npl tx y / TX_L --> %d\n", data->pl_y, (data->pl_tx_y) % 20);
}

void	move_left(t_data *data)
{
	if ((data->pl_tx_y - TX_L / 2) % TX_L == 0 && ((data->pl_tx_x - TX_L / 2) % TX_L == 0 && data->map[data->pl_y][data->pl_x - 1] == '1'))
	{
		printf("wall next, y grade, exit\n");
		return ;
	}
	else if ((data->pl_tx_x - TX_L / 2) % TX_L == 0 && ((data->pl_tx_y - TX_L/2) % TX_L != 0))
	{
		if (data->pl_tx_y % TX_L < TX_L/2)
		{
			if (data->map[data->pl_y][data->pl_x - 1] == '1' || data->map[data->pl_y - 1][data->pl_x - 1] == '1')
				return;
		}
		else
		{
			if (data->map[data->pl_y][data->pl_x - 1] == '1' || data->map[data->pl_y + 1][data->pl_x - 1] == '1')
				return;
		}
	}
	if ((data->pl_tx_x - MOVE) % TX_L == 0 && data->map[data->pl_y][data->pl_x - 1] == '0')
	{
		printf("entered moving\n");
		data->map[data->pl_y][data->pl_x - 1] = data->player;
		data->map[data->pl_y][data->pl_x] = '0';
		data->pl_x--;
	}
	//draw_text(data);
	draw_map(data->map, data->map_h, data->map_l, data);
	data->pl_tx_x -= MOVE;
	data->ray.x -= MOVE;
	draw_circle(data, TX_L/2, data->pl_tx_x, data->pl_tx_y, 0xFF0000);
    ray_till_wall(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	//printf("pl y --> %d\npl tx y / TX_L --> %d\n", data->pl_y, (data->pl_tx_y) % 20);
}

void	move_angle_l(t_data *data)
{
	printf("pa beofre is %.2f\n", data->pa);
	if (data->pa > 0.0 - 0.01 && data->pa < 0.0 + 0.01)
		data->pa = 2 * M_PI;
	data->pa -= M_PI/24;
	printf("palater is %.2f\n\n", data->pa);
	data->ray.x = data->pl_tx_x + 50 * cos(data->pa);
	data->ray.y = data->pl_tx_y + 50 * sin(data->pa);
	//printf("x is %.0f  y is %.0f\n", data->ray.x, data->ray.y);
	draw_map(data->map, data->map_h, data->map_l, data);
	draw_circle(data, TX_L/2, data->pl_tx_x, data->pl_tx_y, 0xFF0000);
	if (data->pa > 0.00 - 0.1 && data->pa < 0.00 + 0.1)
	{
		printf("PA IS %.2f\n", data->pa);
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
		return;
	}
	if ((data->pa > M_PI - 0.1 && data->pa < M_PI + 0.1))
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
		return;
	}
	ray_till_wall(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return ;
}

void	move_angle_r(t_data *data)
{
	data->pa += M_PI/24;
	printf("pa beofre is %.2f\n", data->pa);
	if (data->pa > 2 * M_PI - 0.01 && data->pa < 2 * M_PI + 0.01)
	{
		data->pa = 0;
	}
	printf("palater is %.2f\n\n", data->pa);
	data->ray.x = data->pl_tx_x + 50 * cos(data->pa);
	data->ray.y = data->pl_tx_y + 50 * sin(data->pa);
	draw_map(data->map, data->map_h, data->map_l, data);
	draw_circle(data, TX_L/2, data->pl_tx_x, data->pl_tx_y, 0xFF0000);
	if ((data->pa > M_PI - 0.1 && data->pa < M_PI + 0.1))
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
		return;
	}
	if (data->pa > 0.00 - 0.1 && data->pa < 0.00 + 0.1)
	{
		printf("PA IS %.2f\n", data->pa);
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
		return;
	}
	ray_till_wall(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
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
	printf("pl y --> %dpl x -->%d\n", data->pl_tx_y, data->pl_tx_x);
	printf("y --> %dx -->%d\n", data->pl_y, data->pl_x);
	// for (int i = 0; i < data->map_h; i++)
	// 	printf("%s\n", data->map[i]);
	// printf("pl y --> %d\npl tx y / TX_L --> %d\n", data->pl_y, (data->pl_tx_y - 100) % 20);
	// printf("pl x --> %d\npl tx x / TX_L --> %d\n\n", data->pl_x, (data->pl_tx_x - 50) % 20);
	return (0);
}

void	dda_2(int num, t_data *data, double x1, double xinc, double y2, double yinc, int color)
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

void dda(t_data *data, double x2, double y2, int color)
{
    double dx;
    double dy;
    double	xinc;
    double	yinc;
    double steps;
    int	i = 0;

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

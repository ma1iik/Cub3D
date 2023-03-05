/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:34:17 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/05 18:56:50 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_map(char **map, int rows, int cols, t_data *data)
{
	int i, j;
	int x, y;
	int color;
	int grid;

	y = 0;
	for (i = 0; i < rows; i++)
	{
		x = 0;
		for (j = 0; j < cols; j++)
		{
			if (map[i][j] == '1')
				color = 0x444444;
			else if (map[i][j] == '0' || ft_ischar(map[i][j]))
				color = 0xFFFFFF;
			else
				color = 0x000000;
			for (int k = 0; k < TX_L; k++)
			{
				for (int l = 0; l < TX_L; l++)
				{
					if (k == 0 || l == 0 || k == TX_L - 1 || l == TX_L - 1)
						my_mlx_pixel_put(data, x + l, y + k, 0x000000);
					else
						my_mlx_pixel_put(data, x + l, y + k, color);
				}
			}
			x += TX_L;
		}
		y += TX_L;
	}
}

// void	draw_circle(t_data *data, int rad, int x, int y, int color)
// {
// 	int radius = rad;
// 	for (int i = x + 1 - radius; i <= x - 1 + radius; i++)
// 	{
// 		for (int j = y + 1 - radius; j <= y - 1 + radius; j++)
// 		{
// 			int distance = (i - x) * (i - x) + (j - y) * (j - y);
// 			if (distance <= radius * radius)
// 			{
// 				my_mlx_pixel_put(data, i, j, color);
// 			}
// 		}
// 	}
// }

void draw_char(char **map, int rows, int cols, t_data *data)
{
	int	i, j;
	int x, y;

	y = 0;
	for (i = 0; i < rows; i++)
	{
		x = 0;
		for (j = 0; j < cols; j++)
		{
			if (ft_ischar(map[i][j]))
			{
				data->player = map[i][j];
				data->pl_tx_y = y + TX_L / 2;
				data->pl_tx_x = x + TX_L / 2;
				ft_direction(data, map[i][j]);
				return ;
				// draw_circle(data,  TX_L/2, x + TX_L/2, y + TX_L/2, 0xFF0000);
			}
			x += TX_L;
		}
		y += TX_L;
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

int check_exist(t_data *data, t_ray *ray, int n)
{
	int		x;
	int		y;

	if (n == 1)
	{
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
	else if (n == 2)
	{
		x = (int)ray->bx / TX_L;
		y = (int)ray->by / TX_L;
		// printf("x is %d y is %d\n", x, y);
		// printf("l is %d h is %d\n", data->map_l, data->map_h);
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
	return (0);
}

void find_wall_a(t_data *data, t_ray *ray, double agl)
{
	double	ya;
	double	xa;

	ya = 0;
	if ((agl > 0 - 0.0001 && agl < 0 + 0.0001)
		|| (agl > 2 * M_PI - 0.0001 && agl < 2 * M_PI + 0.0001))
	{
		ray->ay = data->pl_tx_y;
		ray->ax = data->map_l * TX_L;
		return ;
	}
	else if (agl > M_PI - 0.0001 && agl < M_PI + 0.0001)
	{
		ray->ax = 0;
		ray->ay = data->pl_tx_y;
		return ;
	}
	else if (agl <= M_PI && agl >= 0)
	{
		ya -= TX_L;
		ray->ay = floor(data->pl_tx_y / TX_L) * (TX_L) - 0.00000001;
	}
	else
	{
		ya = TX_L;
		ray->ay = floor(data->pl_tx_y / TX_L) * (TX_L) + TX_L;
	}
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

void find_wall_b(t_data *data, t_ray *ray, double agl)
{
	double	ya;
	double	xa;

	xa = 0;
	ray->bx = 0;
	ray->by = 0;
	if (agl < 3 * M_PI / 2 + 0.001 && agl > 3 * M_PI / 2 - 0.001)
	{
		ray->by = TX_L * data->map_h;
		ray->bx = data->pl_tx_x;
		return ;
	}
	else if (agl < M_PI / 2 + 0.001 && agl > M_PI / 2 - 0.001)
	{
		ray->by = 0;
		ray->bx = data->pl_tx_x;
		return ;
	}
	else if (agl < 3 * M_PI / 2 && agl > M_PI / 2)
	{
		xa = -TX_L;
		ray->bx = floor((double)data->pl_tx_x / TX_L) * (TX_L) - 0.00000001;
	}
	else
	{
		xa = TX_L;
		ray->bx = floor((double)data->pl_tx_x / TX_L) * (TX_L) + TX_L;
	}
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
	double	ang_diff;

	a = sqrtf(pow(data->pl_tx_x - ray->ax, 2)
			+ pow(data->pl_tx_y - ray->ay, 2));
	b = sqrtf(pow(data->pl_tx_x - ray->bx, 2)
			+ pow(data->pl_tx_y - ray->by, 2));
	if (a < b)
	{
		ray->x_fnl = ray->ax;
		ray->y_fnl = ray->ay;
		//printf("x[%.1f]y[%.1f]\n", data->x_fnl, data->y_fnl);
		//data->mure_vertical = 0;
	}
	else
	{
		//printf("plx[%d]ply[%d]\nx[%.2f]y[%.2f]\n", data->pl_tx_x, data->pl_tx_y, ray->bx, ray->by);
		ray->x_fnl = ray->bx;
		ray->y_fnl = ray->by;
		//data->mure_vertical = 1;
	}
	// printf("x[%.1f]y[%.1f]\n", data->x_fnl, data->y_fnl);
	ang_diff = data->pa - agl;
	cos_ang = cos(ang_diff);
	ray->distance = sqrt((pow(data->pl_tx_x - ray->x_fnl, 2) + pow(data->pl_tx_y - ray->y_fnl, 2)));
	ray->distance = ray->distance * cos_ang;
}

void	draw_wall(t_data *data, t_ray *ray, int x, float wall_h)
{
	int	wall_top;
	int	wall_bottom;
	int	color;
	int	mirrored_x;

	wall_top = (HEIGHT - ray->wall_h) / 2;
	wall_bottom = wall_top + wall_h;
	//printf("wall top is %f\n", ray->wall_h);
	for (int y = 0; y < HEIGHT; y++)
	{
		if (y >= wall_top && y < wall_bottom)
		{
			color = 0xFF0000;
			mirrored_x = WIDTH - x - 1;
			my_mlx_pixel_put(data, mirrored_x, y, color);
		}
	}
}

void draw_background(t_data *data)
{
	int	x;
	int	y;

	for (y = 0; y < HEIGHT / 2; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			my_mlx_pixel_put(data, x, y, 0x0000FF);
		}
	}
	for (y = HEIGHT / 2; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			my_mlx_pixel_put(data, x, y, 0x8B4513);
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

void    loop_ext(t_data *data, t_ray *ray, double agl, int x, double cor_dis)
{
	(void)x;
	(void)cor_dis;
	find_wall_a(data, ray, agl);
	find_wall_b(data, ray, agl);
	compare_a_b(data, ray, agl);
	ray->plane = (WIDTH/2) / tan(30);
	ray->wall_h = abs((int)(TX_L / ray->distance * ray->plane));
	draw_wall(data, ray, x, ray->wall_h);
	//dda(data, ray->x_fnl, ray->y_fnl, 0xFF0000);
}

void    cast_rays1(t_data *data)
{
	int		i;
	double	agl;
	double	fov;
	double	cor_dis;

	i = 0;
	agl = add_angle(data->pa, -FOV / 2);
	fov = FOV / WIDTH;
	//draw_map(data->map, data->map_h, data->map_l, data);
	//draw_circle(data, TX_L/6, data->pl_tx_x, data->pl_tx_y, 0xFF0000);
	cor_dis = ft_cor_dis(data, &data->ray[WIDTH/2], data->pa, i);
	draw_background(data);
	data->r_distance = cor_dis;
	while (i < WIDTH)
	{
		loop_ext(data, &data->ray[i], agl, i, cor_dis);
		if (i == WIDTH / 2)
		{
			//printf("agl %.2f\n", data->pa);
			loop_ext(data, &data->ray[i], agl, i, cor_dis);
			data->x_fnl = data->ray[i].x_fnl;
			data->y_fnl = data->ray[i].y_fnl;
			//dda(data, data->x_fnl, data->y_fnl, 0x00FF00);
		}
		agl = add_angle(agl, fov);
		i++;
	}
	//printf("py[%.2f]px[%.2f]\n", data->pl_tx_y, data ->pl_tx_x);
	//printf("y_fnl[%.2f]x_fnl[%.2f]\n", data->y_fnl, data ->x_fnl);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	init_draw(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello world!");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	//draw_map(data->map, data->map_h, data->map_l, data);
	draw_char(data->map, data->map_h, data->map_l, data);
	cast_rays1(data);
}

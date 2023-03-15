/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:34:17 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/15 19:35:04 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    loop_ext(t_data *data, t_ray *ray, double agl, int x, double cor_dis)
{
	(void)x;
	(void)cor_dis;
	find_wall_a(data, ray, agl);
	find_wall_b(data, ray, agl);
	compare_a_b(data, ray, agl);
	ray->plane = (WIDTH / 2) / tan(FOV / 2);
	ray->wall_h = abs((int)(TX_L / ray->distance * ray->plane));
}

void	draw_wall_1(t_data *data , t_ray *ray, double agl)
{
	if (data->w_vertical == 1)
	{
		if (agl < M_PI / 2 && agl > 3 * M_PI * 2)
		{
			data->texture.a_fnl = (int *)data->texture.a_ea;
		}
		else
		{
			data->texture.a_fnl = (int *)data->texture.a_we;
		}
		data->texture.txt_x = fmod(ray->y_fnl / 64.0, 1.0) * 64.0;
	}
	else
	{
		if (agl < M_PI && agl > 0)
		{
			data->texture.a_fnl = (int *)data->texture.a_no;
		}
		else
		{
			data->texture.a_fnl = (int *)data->texture.a_so;
		}
		data->texture.txt_x = fmod(ray->x_fnl / 64.0, 1.0) * 64.0;
	}
	data->draw_height = fabs(64 / data->wl) * ray->plane;
}

void	cast_rays2(t_data *data, double agl, double fov, double cor_dis)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		if (i != WIDTH / 2)
			loop_ext(data, &data->ray[i], agl, i, cor_dis);
		else
		{
			loop_ext(data, &data->ray[i], agl, i, cor_dis);
			data->x_fnl = data->ray[i].x_fnl;
			data->y_fnl = data->ray[i].y_fnl;
		}
		draw_wall_1(data, &data->ray[i], agl);
		draw_wall(data, &data->ray[i], i, agl);
		agl = add_angle(agl, fov);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	cast_rays1(t_data *data)
{
	double	agl;
	double	fov;
	double	cor_dis;

	agl = add_angle(data->pa, -FOV / 2);
	fov = FOV / WIDTH;
	cor_dis = ft_cor_dis(data, &data->ray[WIDTH / 2], data->pa, 0);
	draw_background(data);
	data->r_distance = cor_dis;
	cast_rays2(data, agl, fov, cor_dis);
}

void	init_draw(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello world!");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	data->texture.ea = mlx_xpm_file_to_image(data->mlx, data->texture.ea_fn,
			&data->texture.img_w, &data->texture.img_h);
	data->texture.no = mlx_xpm_file_to_image(data->mlx, data->texture.no_fn,
			&data->texture.img_w, &data->texture.img_h);
	data->texture.we = mlx_xpm_file_to_image(data->mlx, data->texture.we_fn,
			&data->texture.img_w, &data->texture.img_h);
	data->texture.so = mlx_xpm_file_to_image(data->mlx, data->texture.so_fn,
			&data->texture.img_w, &data->texture.img_h);
	data->texture.a_ea = (int *)mlx_get_data_addr(data->texture.ea,
			&data->texture.ea_bpp, &data->texture.ea_l, &data->texture.ea_end);
	data->texture.a_no = (int *)mlx_get_data_addr(data->texture.no,
			&data->texture.no_bpp, &data->texture.no_l, &data->texture.no_end);
	data->texture.a_we = (int *)mlx_get_data_addr(data->texture.we,
			&data->texture.we_bpp, &data->texture.we_l, &data->texture.we_end);
	data->texture.a_so = (int *)mlx_get_data_addr(data->texture.so,
			&data->texture.no_bpp, &data->texture.so_l, &data->texture.so_end);
	draw_char(data->map, data->map_h, data->map_l, data);
	cast_rays1(data);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 01:27:23 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/12 18:54:56 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_fill_map(t_data *data, char *file)
{
	char	*l;
	int		gnl;
	int		i;
	int		j;
	int		fd;

	gnl = 1;
	i = 0;
	j = 0;
	fd = open(file, O_RDONLY);
	data->map_h = data->m_ll - data->m_fl + 1;
	printf ("%d height\n", data->map_h);
	printf ("%d fl\n", data->m_fl);
	printf ("%d ll\n", data->m_ll);
	data->map = ft_calloc(sizeof(char *), data->map_h + 1);
	data->map_star = ft_calloc(sizeof(char *), data->map_h + 1);
	if (!data->map)
		return (WRONG);
	while (gnl >= 0)
	{
		//printf("times %d\n", times++);
		gnl = get_next_line(fd, &l);
		//printf("fl[%d] ll[%d]\n", data->m_fl, data->m_ll);
		if (gnl == 0)
		{
			if (j >= data->m_fl && j <= data->m_ll)
			{
				data->map[i++] = ft_strdup(l);
			}
			break;
		}
		if (j >= data->m_fl && j <= data->m_ll)
		{
			data->map[i++] = ft_strdup(l);
		}
		free (l);
		j++;
	}
	data->map[i] = '\0';
	close (fd);
	if (ft_fill_map2(data) == WRONG)
		return (WRONG);
	if (ft_fill_map3(data) == WRONG)
		return (WRONG);
	return (RIGHT);
}

int	ft_fill_map2(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	data->map_l = ft_map_len(data);
	while (data->map[i])
	{
		j = 0;
		tmp = ft_calloc(ft_map_len(data) + 1, sizeof(char));
		if (!tmp)
			return (WRONG);
		while (data->map[i][j])
		{
			tmp[j] = data->map[i][j];
			j++;
		}
		while (j < ft_map_len(data))
			tmp[j++] = ' ';
		tmp[j] = '\0';
		free (data->map[i]);
		data->map[i] = tmp;
		i++;
	}
	return (RIGHT);
}

int	ft_fill_map3(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	data->map_l = ft_map_len(data);
	while (data->map[i])
	{
		j = 0;
		tmp = ft_calloc(ft_map_len(data) + 1, sizeof(char));
		if (!tmp)
			return (WRONG);
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ')
				tmp[j] = '*';
			else
				tmp[j] = data->map[i][j];
			j++;
		}
		tmp[j] = '\0';
		data->map_star[i] = tmp;
		i++;
	}
	return (RIGHT);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_length + x
			* (data->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_direction(t_data *data, char player)
{
	if (player == 'N')
	{
		data->pa = M_PI / 2;
	}
	else if (player == 'E')
	{
		data->pa = 0.0000;
	}
	else if (player == 'S')
	{
		data->pa = 3 * M_PI / 2;
	}
	else if (player == 'W')
	{
		data->pa = M_PI;
	}
	return ;
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (ft_parsing(ac, data, av[1]) == WRONG)
		return (WRONG);
	init_draw(data);
	//find_hit_point(data, data->pl_tx_x, data->pl_tx_y, data->pa);
	//printf("x=%d  y=%d\n", data->pl_tx_x, data->pl_tx_y);
	//ray_till_wall_v(data);
	//printf("y is --> %d\nx is --> %d\n", data->pl_tx_y, data->pl_tx_x);
	//printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y - 100) % 20);
	mlx_hook(data->win, ON_DESTROY, 0, ft_exit, NULL);
	mlx_hook(data->win, ON_KEYDOWN, 1L<<0, ft_action, data);
	mlx_key_hook(data->win, ft_release, data);
	mlx_loop(data->mlx);
}

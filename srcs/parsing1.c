/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:19:02 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/15 19:29:59 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	stock_txt(t_data *data, char *l)
{
	if (is_ident(data, l))
		do_ident(data, l);
	else if (is_col(data, l))
		do_col(data, l);
	else if (is_empty(data, l))
		;
	else
	{
		ft_error(9);
		exit(1);
	}
}

int	check_stock_txt(t_data *data, char *l)
{
	if (is_ident(data, l))
		do_ident(data, l);
	else if (is_col(data, l))
		do_col(data, l);
	else if (is_empty(data, l))
		;
	else
		return (1);
	return (0);
}

void	txt_init(t_data *data)
{
	data->texture.type = 0;
	data->texture.l_i = 0;
	data->texture.ea_n = 0;
	data->texture.so_n = 0;
	data->texture.no_n = 0;
	data->texture.we_n = 0;
	data->texture.f_n = 0;
	data->texture.c_n = 0;
	data->m_fl = 0;
}

int	ft_fill_txt(t_data *data, int fd)
{
	char	*l;
	int		gnl;

	gnl = 1;
	txt_init(data);
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &l);
		if (data->texture.type == 6)
		{
			if (check_stock_txt(data, l) == 1 && data->m_fl == 0)
				data->m_fl = data->texture.l_i;
			if (check_stock_txt(data, l) == 1 && data->m_fl != 0)
				data->m_ll = data->texture.l_i;
		}
		else
			stock_txt(data, l);
		data->texture.l_i++;
		free (l);
	}
	if (data->texture.type > 6)
	{
		ft_error(9);
	}
	return (RIGHT);
}

int ft_parsing(int ac, t_data *data, char *file)
{
	int		fd;

	if (ac != 2)
		return (ft_error(0));
	fd = open(file, O_RDONLY);
	if (ft_check_ext(data, file) == WRONG)
		return (WRONG);
	if (ft_fill_txt(data, fd) == WRONG)
		return (WRONG);
	data->map_h = data->m_ll - data->m_fl + 1;
	data->map = ft_calloc(sizeof(char *), data->map_h + 1);
	data->map_star = ft_calloc(sizeof(char *), data->map_h + 1);
	if (!data->map || !data->map_star)
		return (WRONG);
	if (ft_fill_map(data, file, 0, 0) == WRONG)
		return (WRONG);
	if (ft_wrongchar(data, 0, 0, 0) == WRONG)
		return (WRONG);
	if (ft_checkwalls(data) == WRONG)
		return (WRONG);
	if (ft_checkways(data->pl_y, data->pl_x, data->map_star, data) == WRONG)
		return (WRONG);
	close(fd);
	return (RIGHT);
}

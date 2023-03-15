/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:19:02 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/15 19:25:02 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	do_ident(t_data *data, char *l)
{
	char	*text;
	int		i;
	int		j;

	i = 2;
	data->texture.type++;
	while (ft_isspace(l[i]))
		i++;
	j = i;
	while (l[j] && !(ft_isspace(l[j])))
		j++;
	text = ft_substr(l, i, j - i);
	while (ft_isspace(l[j]))
		j++;
	if (!(ft_isspace(l[j])))
	{
		if (j == ft_strlen(l))
			text_exst(data, text, l);
		else
		{
			free(text);
			printf("Error\ntexture handling\n");
			exit(1);
		}
	}
}

void check_ident(t_data *data)
{
	if (data->texture.ea_n > 1 || data->texture.so_n > 1
		|| data->texture.we_n > 1 || data->texture.no_n > 1)
	{
		ft_error(9);
		exit (1);
	}
}

void check_col(t_data *data)
{
	if (data->texture.f_n > 1 || data->texture.c_n > 1)
	{
		ft_error(9);
		exit (1);
	}
}

int is_ident2(t_data *data, char *l)
{
	if (ft_strncmp(l, "SO", 2) == 0 && ft_isspace(l[2]))
	{
		data->texture.so_n++;
		check_ident(data);
		return (1);
	}
	else if (ft_strncmp(l, "WE", 2) == 0 && ft_isspace(l[2]))
	{
		data->texture.we_n++;
		check_ident(data);
		return (1);
	}
	else
		return (0);
}

int is_ident(t_data *data, char *l)
{
	if (ft_strncmp(l, "EA", 2) == 0 && ft_isspace(l[2]))
	{
		data->texture.ea_n++;
		check_ident(data);
		return (1);
	}
	else if (ft_strncmp(l, "NO", 2) == 0 && ft_isspace(l[2]))
	{
		data->texture.no_n++;
		check_ident(data);
		return (1);
	}
	if (is_ident2(data, l))
		return (1);
	return (0);
}
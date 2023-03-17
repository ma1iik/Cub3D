/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:19:02 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/17 20:46:40 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_rowsbetween(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 1;
	while (i < data->map_h - 1)
	{
		j = 0;
		while (map[i][j] == '*')
			j++;
		if (map[i][j] != '1')
			return (ft_error(8));
		j = data->map_l - 1;
		while (map[i][j] == '*')
			j--;
		if (map[i][j] != '1')
			return (ft_error(8));
		i++;
	}
	return (RIGHT);
}

void	texture_extns(char *texture)
{
	int	l;

	l = ft_strlen(texture);
	while (l > 0)
	{
		if (texture[l] == '.')
		{
			if ((texture[l + 1] != 'x') || (texture[l + 2] != 'p')
				|| ((texture[l + 3] != 'm') || (texture[l + 4])))
			{
				printf("Error\nPath extension invalid!\n");
				exit(1);
			}
		}
		l--;
	}
}

void	text_exst1(t_data *data, char *text, char *l)
{
	int		fd;

	if (ft_strncmp(l, "NO", 2) == 0 && (ft_isspace(l[2])))
	{
		texture_extns(text);
		fd = open(text, O_DIRECTORY);
		if (fd > 0)
		{
			close(fd);
			ft_error(10);
		}
		close(fd);
		fd = open(text, O_RDONLY);
		if (fd == -1)
		{
			close(fd);
			ft_error(11);
		}
		close(fd);
		data->texture.no_fn = ft_strdup(text);
		free(text);
	}
}

void	text_exst2(t_data *data, char *text, char *l)
{
	int		fd;

	if (ft_strncmp(l, "SO", 2) == 0 && (ft_isspace(l[2])))
	{
		texture_extns(text);
		fd = open(text, O_DIRECTORY);
		if (fd > 0)
		{
			close(fd);
			ft_error(10);
		}
		close(fd);
		fd = open(text, O_RDONLY);
		if (fd == -1)
		{
			close(fd);
			ft_error(11);
		}
		close(fd);
		data->texture.so_fn = ft_strdup(text);
		free(text);
	}
}

void	text_exst3(t_data *data, char *text, char *l)
{
	int		fd;

	if (ft_strncmp(l, "WE", 2) == 0 && (ft_isspace(l[2])))
	{
		texture_extns(text);
		fd = open(text, O_DIRECTORY);
		if (fd > 0)
		{
			close(fd);
			ft_error(10);
		}
		close(fd);
		fd = open(text, O_RDONLY);
		if (fd == -1)
		{
			close(fd);
			ft_error(11);
		}
		close(fd);
		data->texture.we_fn = ft_strdup(text);
		free(text);
	}
}

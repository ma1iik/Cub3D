/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:19:02 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/12 18:54:32 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_check_ext(t_data *data, char *file)
{
	int	len;
	int	fd;

	len = ft_strlen(file) - 1;
	(void)data;
	if (!(file[len] == 'b' && file[len - 1] == 'u' && file[len - 2]
			== 'c' && file[len - 3] == '.' && len > 3))
		return (ft_error(1));
	fd = open(file, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		return (ft_error(2));
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		close (fd);
		return (ft_error(3));
	}
	close(fd);
	return (RIGHT);
}

int	ft_wrongchar(t_data *data)
{
	int	i;
	int	j;
	int	num;

	i = 0;
	num = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != '1' && data->map[i][j] != '0'
				&& data->map[i][j] != 'N'
			&& data->map[i][j] != 'S' && data->map[i][j] != 'W'
				&& data->map[i][j] != 'E' && data->map[i][j] != ' ')
				return (ft_error(4));
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->pl_x = j;
				data->pl_y = i;
				num++;
			}
			j++;
		}
		i++;
	}
	if (num != 1)
		return (ft_error(5));
	return (RIGHT);
}

int	ft_checkways1(int x, int y, char **map, t_data *data)
{
	if (x < 0 || x >= data->map_h || y < 0 || y >= data->map_l)
		return (0);
	if (map[x][y] == '1')
		return (0);
	map[x][y] = 'B';
	if (map[x - 1][y] && map[x - 1][y] == '0')
		ft_checkways1(x - 1, y, map, data);
	if (map[x + 1][y] && map[x + 1][y] == '0')
		ft_checkways1(x + 1, y, map, data);
	if (map[x][y - 1] && map[x][y - 1] == '0')
		ft_checkways1(x, y - 1, map, data);
	if (map[x][y + 1] && map[x][y + 1] == '0')
		ft_checkways1(x, y + 1, map, data);
	return (1);
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
				printf("Error: Extension path invalid!\n");
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

void	text_exst4(t_data *data, char *text, char *l)
{
	int		fd;

	if (ft_strncmp(l, "EA", 2) == 0 && (ft_isspace(l[2])))
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
		data->texture.ea_fn = ft_strdup(text);
		free(text);
	}
}

void	text_exst(t_data *data, char *text, char *l)
{
	text_exst1(data, text, l);
	text_exst2(data, text, l);
	text_exst3(data, text, l);
	text_exst4(data, text, l);
}

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
			printf("Error: texture handling\n");
			exit(1);
		}
	}
}

void check_ident(t_data *data)
{
	if (data->texture.ea_n > 1 || data->texture.so_n > 1 || data->texture.we_n > 1 || data->texture.no_n > 1)
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
	else if (ft_strncmp(l, "SO", 2) == 0 && ft_isspace(l[2]))
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

int	is_col(t_data *data, char *l)
{
	if (ft_strncmp(l, "F", 1) == 0 && ft_isspace(l[1]))
	{
		data->texture.f_n++;
		check_col(data);
		return (1);
	}
	else if (ft_strncmp(l, "C", 1) == 0 && ft_isspace(l[1]))
	{
		data->texture.c_n++;
		check_col(data);
		return (1);
	}
	return (0);
}

int	is_empty(t_data *data, char *l)
{
	int	i;
	int	len;

	i = 0;
	(void)data;
	len = ft_strlen(l);
	if (l[i] == 0)
		return (1);
	while (ft_isspace(l[i]))
		i++;
	if (i == len)
		return (1);
	return (0);
}

void check_col_content(char *col)
{
	int	i;

	i = 0;
	while (col[i])
	{
		if (col[i] != ',' && (!(ft_isdigit(col[i])))
			&& (ft_isspace(col[i]) != 1))
		{
			printf("Error: Invalid color parameter for floor or celling\n");
			free(col);
			exit(1);
		}
		i++;
	}
}

int	col_range(int r, int g, int b)
{
	if (r < 0 || r > 255)
	{
		printf("Error: Color value invalid!\n");
		return (0);
	}
	if (g < 0 || g > 255)
	{
		printf("Error: Color value invalid!\n");
		return (0);
	}
	if (b < 0 || b > 255)
	{
		printf("Error: Color value invalid!\n");
		return (0);
	}
	return (1);

}

void	col_def_f(char **col_tab, t_data *data)
{
	int	i;

	i = 0;
	while (col_tab[i])
		i++;
	if (i != 3)
	{
		printf("Error: Wrong number of color arguments\n");
		exit(1);
	}
	i = 0;
	while (i < 3)
	{
		if (i == 0)
			data->f_r = ft_atoi(col_tab[i]);
		if (i == 1)
			data->f_g = ft_atoi(col_tab[i]);
		if (i == 2)
			data->f_b = ft_atoi(col_tab[i]);
		i++;
	}
	if (!(col_range(data->f_r, data->f_g, data->f_b)))
		exit (1);
}

void	col_def_c(char **col_tab, t_data *data)
{
	int	i;

	i = 0;
	while (col_tab[i])
		i++;
	if (i != 3)
	{
		printf("Error: Wrong number of color arguments\n");
		exit(1);
	}
	i = 0;
	while (i < 3)
	{
		if (i == 0)
			data->c_r = ft_atoi(col_tab[i]);
		if (i == 1)
			data->c_g = ft_atoi(col_tab[i]);
		if (i == 2)
			data->c_b = ft_atoi(col_tab[i]);
		i++;
	}
	if (!(col_range(data->c_r, data->c_g, data->c_b)))
		exit (1);
}

void	ft_floorc(t_data *data, char *col, char **colors, char *l)
{
	int	i;

	i = 0;
	if ((l[0] == 'F') && (ft_isspace(l[1])))
	{
		check_col_content(col);
		colors = ft_split(col, ',');
		col_def_f(colors, data);
		free(col);
		while (colors[i])
			free(colors[i++]);
		free(colors);
	}
}

void	ft_cellc(t_data *data, char *col, char **colors, char *l)
{
	int	i;

	i = 0;
	if ((l[0] == 'C') && (ft_isspace(l[1])))
	{
		check_col_content(col);
		colors = ft_split(col, ',');
		col_def_c(colors, data);
		free(col);
		while (colors[i])
			free(colors[i++]);
		free(colors);
	}
}

void	col_exst(t_data *data, char *col, char *l)
{
	char	**colors;

	
	colors = NULL;
	ft_floorc(data, col, colors, l);
	ft_cellc(data, col, colors, l);
}

void	do_col(t_data *data, char *l)
{
	int		i;
	char	*col;
	int		len;

	i = 1;
	data->texture.type++;
	len = ft_strlen(l);
	while (ft_isspace(l[i]))
		i++;
	while ((ft_isspace(l[--len])))
		;
	col = ft_substr(l, i, len - i + 1);
	col_exst(data, col, l);
}

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
			if(check_stock_txt(data, l) == 1 && data->m_fl == 0)
				data->m_fl = data->texture.l_i;
			if(check_stock_txt(data, l) == 1 && data->m_fl != 0)
				data->m_ll = data->texture.l_i;
		}
		else
		{
			//printf("%s\n", l);
			stock_txt(data, l);
		}
		data->texture.l_i++;
		free (l);
		//printf("type is %d\n", data->texture.type);
	}
	if (data->texture.type > 6)
	{
		ft_error(9);
		exit(1);
	}
	return (RIGHT);
}

int ft_parsing(int ac, t_data *data, char *file)
{
	int		fd;

	if (ac != 2)
		return (ft_error(0));
	//data->map = ft_calloc(sizeof(char *), ft_mapsize(file) + 1);
	//data->map_star = ft_calloc(sizeof(char *), ft_mapsize(file) + 1);
	//data->map_h = ft_mapsize(file);
	//printf("%d\n", data->map_h);
	//printf("LOL\n");
	fd = open(file, O_RDONLY);
	if (ft_check_ext(data, file) == WRONG)
		return (WRONG);
	if (ft_fill_txt(data, fd) == WRONG)
		return (WRONG);
	if (ft_fill_map(data, file) == WRONG)
		return (WRONG);
	if (ft_wrongchar(data) == WRONG)
		return (WRONG);
	if (ft_checkwalls(data) == WRONG)
		return (WRONG);
	if (ft_checkways(data->pl_y, data->pl_x, data->map_star, data) == WRONG)
		return (WRONG);
	close(fd);
	return (RIGHT);
}

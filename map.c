/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:57:40 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/01 23:01:32 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static size_t	get_map_len(char *ber)
{
	int		fd;
	char	buf[1024];
	size_t	size;
	size_t	tmp_read;

	fd = open(ber, O_RDONLY);
	if (fd < 0 || read(fd, buf, 0) < 0)
		no_such_file_error();
	size = 0;
	tmp_read = read(fd, buf, 1024);
	while (tmp_read > 0)
	{
		size += tmp_read;
		tmp_read = read(fd, buf, 1024);
	}
	close(fd);
	return (size);
}

static bool	map_contains_0epc(t_map *map, char *tmp_map)
{
	size_t	door;
	size_t	player;
	size_t	o;
	size_t	x;

	door = 0;
	player = 0;
	x = 0;
	o = 0;
	map->coins = 0;
	while (tmp_map[x] && door < 2 && player < 2)
	{
		if (tmp_map[x] == 'C')
			map->coins++;
		if (tmp_map[x] == '0')
			o++;
		if (tmp_map[x] == 'E')
			door++;
		if (tmp_map[x] == 'P')
			player++;
		if (tmp_map[x + 1] && tmp_map[x] == '\n' && tmp_map[x +1] == '\n')
			return (0);
		x++;
	}
	return ((door == 1 && player == 1 && o != 0 && map->coins != 0));
}

static bool	check_lines(char **map, size_t x, size_t rows)
{
	size_t	y;

	y = 0;
	while (map[x][y])
	{
		if ((x == 0 || x == rows) && map[x][y] != '1')
			return (0);
		y++;
	}
	return (1);
}

static bool	check_walls_and_center(char **map, size_t cols, size_t rows)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (map[x])
	{
		if (!check_lines(map, x, rows))
			return (0);
		if (map[x][0] != '1' || map[x][cols - 1] != '1')
			return (0);
		y = 0;
		while (map[x][y])
		{
			if (!ft_search_char(map[x][y], "01PCE"))
				return (0);
			y++;
		}
		x++;
	}
	x--;
	return (1);
}

static bool	check_map(t_map *map, char *tmp_map)
{
	size_t	x;
	size_t	cols;

	x = 0;
	if (!map->grid[3])
		return (0);
	cols = ft_strlen(map->grid[0]);
	while (map->grid[x + 1])
	{
		if (ft_strlen(map->grid[x + 1]) != cols)
			return (0);	
		x++;
	}
	if (!check_walls_and_center(map->grid, cols, x))
		return (0);
	if (!map_contains_0epc(map, tmp_map))
		return (0);
	map->cols = cols;
	map->rows = x;
	map->status = 1;
	return (1);
}

void	trigger_checks(t_map *map, char *tmp_map)
{
		(*map).grid = ft_split(tmp_map, '\n');
		(*map).copy = ft_split(tmp_map, '\n');
		if (check_map(map, tmp_map) == 0)
		{
			free(tmp_map);
			map_error(map->grid, map->copy);
		}
		if (check_path(map) == 0)
		{
			free(tmp_map);
			map_error(map->grid, map->copy);
		}
}
void	define_map(t_map *map, char *ber)
{
	int		fd;
	size_t	size;
	char	*tmp_map;

	size = get_map_len(ber);
	if (size < 17)
		return ;
	tmp_map = malloc(sizeof(char) * (size + 1));
	if (!tmp_map)
		malloc_error();
	fd = open(ber, O_RDONLY);
	if (fd < 0 || read(fd, tmp_map, 0) < 0)
	{
		free(tmp_map);
		no_such_file_error();
	}
	size = read(fd, tmp_map, size);
	if (size > 0)
	{
		tmp_map[size] = '\0';
		trigger_checks(map, tmp_map);
	}
	free(tmp_map);
	close(fd);
}

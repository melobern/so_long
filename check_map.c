/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:48:53 by mbernard          #+#    #+#             */
/*   Updated: 2024/02/28 19:00:46 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	locate_player(char **map, t_player *player)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'P')
			{
				(*player).x = x;
				(*player).y = y;
				return ;
			}
			y++;
		}
		x++;
	}
}

void	fill_down(t_map *map, size_t x, size_t y);
void	fill_left(t_map *map, size_t x, size_t y);
void	fill_right(t_map *map, size_t x, size_t y);

void	fill_up(t_map *map, size_t x, size_t y)
{
	while ((*map).copy[x][y] != '1' && x != 0)
	{
		(*map).copy[x][y] = 'p';
		if ((*map).copy[x][y - 1] != 'p' && (*map).copy[x][y - 1] != '1')
			fill_left(map, x, y);
		if ((*map).copy[x][y + 1] != 'p' && (*map).copy[x][y + 1] != '1')
			fill_right(map, x, y);
		x--;
	}
}

void	fill_down(t_map *map, size_t x, size_t y)
{
	while ((*map).copy[x][y] != '1' && x != (map->rows))
	{
		(*map).copy[x][y] = 'p';
		x++;
	}
}

void	fill_left(t_map *map, size_t x, size_t y)
{
	while ((*map).copy[x][y] != '1' && y > 0)
	{
		(*map).copy[x][y] = 'p';
		if ((*map).copy[x + 1][y] != 'p' && (*map).copy[x + 1][y] != '1')
			fill_down(map, x, y);
		y--;
	}
}

void	fill_right(t_map *map, size_t x, size_t y)
{
	while ((*map).copy[x][y] != '1' && y != (map->cols))
	{
		(*map).copy[x][y] = 'p';
		if ((*map).copy[x + 1][y] != 'p' && (*map).copy[x + 1][y] != '1')
			fill_down(map, x, y);
		y++;
	}
}

void	fill_paths(t_map map, size_t x, size_t y)
{
	while (map.copy[x][y] != '1' && y != (map.cols))
	{
		fill_down(&map, x, y);
		fill_up(&map, x, y);
		fill_left(&map, x, y);
		fill_right(&map, x, y);
		y++;
	}

}

void	search_fill_free_path(t_map map, size_t rows, size_t cols)
{
	size_t	x;
	size_t	y;

	x = 1;
	while (x < rows)
	{
		y = 1;
		while (y < cols)
		{
			if (map.copy[x][y] == 'p')
				fill_paths(map, x, y);
			y++;
		}
		x++;
	}
}

bool	check_path(t_map map)
{
	t_player	player;
	size_t	x;
	size_t	y;

	locate_player(map.copy, &player);
	fill_paths(map, player.x, player.y);
	search_fill_free_path(map, map.rows, map.cols);
	x = 1;
	y = 1;
	while (x < map.rows)
	{
		y = 1;
		while (y < map.cols)
		{
			if (map.copy[x][y] == 'C' || map.copy[x][y] == 'E')
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:44:09 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/02 10:25:42 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	collect_or_leave(t_data *img, char c, size_t x, size_t y)
{
	if (c == 'C')
	{
		if (img->map.coins != 0)
		{
			img->map.coins--;
			img->map.grid[x][y] = '0';
			printf("%lu coins left !!!\n", img->map.coins);
		}
	}
	else if (c == 'E')
	{
		if (img->map.coins == 0)
		{
			ft_putendl_fd("Congratulations ! You finished the game !", 1);
			ft_putendl_fd("Sprites credits to Cub Noodles ;", 1);
			ft_putendl_fd("https://cupnooble.itch.io/", 1);
			close_window(img);
		}
	}
}

void	move_player_img(t_data *img, size_t x, size_t y, int direction)
{
	size_t	p_x;
	size_t	p_y;

	p_x = img->map.player.x * 80;
	p_y = img->map.player.y * 80;
	if (img->map.grid[x][y] != 'E')
		mlx_put_image_to_window(img->mlx, img->win, img->empty, y * 80, x * 80);
	else if (img->map.grid[x][y] == 'E')
		mlx_put_image_to_window(img->mlx, img->win, img->exit, y * 80, x * 80);
	if (direction == 1)
		mlx_put_image_to_window(img->mlx, img->win, img->up, p_y, p_x);
	else if (direction == 2)
		mlx_put_image_to_window(img->mlx, img->win, img->down, p_y, p_x);
	else if (direction == 3)
		mlx_put_image_to_window(img->mlx, img->win, img->left, p_y, p_x);
	else if (direction == 4)
		mlx_put_image_to_window(img->mlx, img->win, img->right, p_y, p_x);
}

bool	move_up(t_data *img)
{
	size_t	x;
	size_t	y;

	x = img->map.player.x;
	y = img->map.player.y;
	if (img->map.grid[x - 1][y] == '1')
		return (0);
	img->map.player.x -= 1;
	move_player_img(img, x, y, 1);
	collect_or_leave(img, img->map.grid[x - 1][y], x - 1, y);
	return (1);
}

bool	move_down(t_data *img)
{
	size_t	x;
	size_t	y;

	x = img->map.player.x;
	y = img->map.player.y;
	if (img->map.grid[x + 1][y] == '1')
		return (0);
	img->map.player.x += 1;
	move_player_img(img, x, y, 2);
	collect_or_leave(img, img->map.grid[x + 1][y], x + 1, y);
	return (1);
}

bool	move_left(t_data *img)
{
	size_t	x;
	size_t	y;

	x = img->map.player.x;
	y = img->map.player.y;
	if (img->map.grid[x][y - 1] == '1')
		return (0);
	img->map.player.y -= 1;
	move_player_img(img, x, y, 3);
	collect_or_leave(img, img->map.grid[x][y - 1], x, y - 1);
	return (1);
}

bool	move_right(t_data *img)
{
	size_t	x;
	size_t	y;

	x = img->map.player.x;
	y = img->map.player.y;
	if (img->map.grid[x][y + 1] == '1')
		return (0);
	img->map.player.y += 1;
	move_player_img(img, x, y, 4);
	collect_or_leave(img, img->map.grid[x][y + 1], x, y + 1);
	return (1);
}

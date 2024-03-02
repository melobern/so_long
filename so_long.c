/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:10:35 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/02 13:15:40 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_images(t_data *img)
{
	if (img->empty)
		mlx_destroy_image(img->mlx, img->empty);
	if (img->wall)
		mlx_destroy_image(img->mlx, img->wall);
	if (img->coll)
		mlx_destroy_image(img->mlx, img->coll);
	if (img->exit)
		mlx_destroy_image(img->mlx, img->exit);
	if (img->up)
		mlx_destroy_image(img->mlx, img->up);
	if (img->down)
		mlx_destroy_image(img->mlx, img->down);
	if (img->left)
		mlx_destroy_image(img->mlx, img->left);
	if (img->right)
		mlx_destroy_image(img->mlx, img->right);
}

int	close_window(t_data *img)
{
	destroy_images(img);
	if (img->win)
		mlx_destroy_window(img->mlx, img->win);
	if (img->mlx)
	{
		mlx_destroy_display(img->mlx);
		free(img->mlx);
	}
	ft_free_tab(img->map.grid);
	ft_free_tab(img->map.copy);
	exit(1);
	return (0);
}

void	init_images(t_data *img)
{
	int	width;
	int	height;

	width = 80;
	height = 80;
	img->empty = mlx_xpm_file_to_image(img->mlx, img->emp_img, &width, &height);
	img->wall = mlx_xpm_file_to_image(img->mlx, img->wall_img, &width, &height);
	img->coll = mlx_xpm_file_to_image(img->mlx, img->coll_img, &width, &height);
	img->exit = mlx_xpm_file_to_image(img->mlx, img->exit_img, &width, &height);
	img->up = mlx_xpm_file_to_image(img->mlx, img->up_img, &width, &height);
	img->down = mlx_xpm_file_to_image(img->mlx, img->down_img, &width, &height);
	img->left = mlx_xpm_file_to_image(img->mlx, img->left_img, &width, &height);
	img->right = mlx_xpm_file_to_image(img->mlx, img->right_img, &width,
			&height);
	if (!img->empty || !img->wall || !img->coll || !img->exit || !img->up
		|| !img->down || !img->left || !img->right)
	{
		ft_putstr_fd("Error\nMalloc error\n", 2);
		close_window(img);
	}
}

void	init_map(t_data *img, size_t x, size_t y)
{
	while (x <= img->map.rows)
	{
		y = 0;
		while (y <= img->map.cols)
		{
			if (img->map.grid[x][y] == '1')
				mlx_put_image_to_window(img->mlx, img->win, img->wall, y * 80, x
					* 80);
			else if (img->map.grid[x][y] == '0')
				mlx_put_image_to_window(img->mlx, img->win, img->empty, y * 80,
					x * 80);
			else if (img->map.grid[x][y] == 'C')
				mlx_put_image_to_window(img->mlx, img->win, img->coll, y * 80, x
					* 80);
			else if (img->map.grid[x][y] == 'E')
				mlx_put_image_to_window(img->mlx, img->win, img->exit, y * 80, x
					* 80);
			else if (img->map.grid[x][y] == 'P')
				mlx_put_image_to_window(img->mlx, img->win, img->down, y * 80, x
					* 80);
			y++;
		}
		x++;
	}
}

int	key_hook(int keysym, t_data *img)
{
	bool	can_move;

	can_move = 1;
	if (keysym == XK_Escape)
		close_window(img);
	else if (keysym == XK_W || keysym == XK_w)
		can_move = move_up(img);
	else if (keysym == XK_A || keysym == XK_a)
		can_move = move_left(img);
	else if (keysym == XK_S || keysym == XK_s)
		can_move = move_down(img);
	else if (keysym == XK_D || keysym == XK_d)
		can_move = move_right(img);
	if (can_move == 0)
		return (0);
	img->map.player.moves++;
	ft_putstr_fd("Moves :", 1);
	ft_put_pos_nbr_fd(img->map.player.moves, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

bool	ends_by_ber(char *file)
{
	size_t	l;
	size_t	p;
	size_t	b;
	size_t	e;
	size_t	r;

	l = ft_strlen(file);
	if (l < 4)
		return (0);
	p = l - 4;
	b = l - 3;
	e = l - 2;
	r = l - 1;
	if (file[p] == '.' && file[b] == 'b' && file[e] == 'e' && file[r] == 'r')
		return (1);
	return (0);
}

void	init_screen(t_data *img)
{
	init_pictures(img);
	init_images(img);
	init_map(img, 0, 0);
	img->map.player.moves = 0;
}

void	put_hooks(t_data *img)
{
	mlx_key_hook(img->win, key_hook, img);
	mlx_hook(img->win, DestroyNotify, 0, close_window, img);
}

int	main(int ac, char **av)
{
	t_data	img;

	if (ac < 2 || !ends_by_ber(av[1]))
		input_error();
	define_map(&img.map, av[1]);
	if (img.map.status == 0)
		map_error(img.map.grid, img.map.copy);
	img.mlx = mlx_init();
	if (img.mlx == NULL)
	{
		free_tabs(img.map.grid, img.map.copy);
		malloc_error();
	}
	img.win = mlx_new_window(img.mlx, ((img.map.cols) * 80), ((img.map.rows + 1)
				* 80), "so_long");
	if (img.win == NULL)
	{
		mlx_destroy_display(img.mlx);
		free_tabs(img.map.grid, img.map.copy);
		return (free(img.mlx), 1);
	}
	init_screen(&img);
	put_hooks(&img);
	mlx_loop(img.mlx);
	return (0);
}

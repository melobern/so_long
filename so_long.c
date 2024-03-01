/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:10:35 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/01 19:31:17 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Convertir image en xpm pour que ca s affiche correctement
 *
 * verifier qu'il n y a pas deux \n a la suite : si \n et x + 1 == \n...
 * voir les cartes utilisees par chstein
 * hook tout court pour les controles afin de pouvoir rester appuye sur la touche sans que ca ne pose probleme
 * refresh la map a chaque mouvement
 */
#include "so_long.h"

int	close_window(t_data *img)
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
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
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
		write(2, "Error\nMallor error\n", 19);
		close_window(img);
	}
}

void	init_map(t_data *img)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x <= img->map.rows)
	{
		y = 0;
		while (y <= img->map.cols)
		{
                  if (img->map.grid[x][y] == '1')
                    mlx_put_image_to_window(img->mlx, img->win, img->wall, y * 80, x * 80);
                  else if (img->map.grid[x][y] == '0')
			mlx_put_image_to_window(img->mlx, img->win, img->empty, y * 80, x * 80);
                  else if (img->map.grid[x][y] == 'C')
			mlx_put_image_to_window(img->mlx, img->win, img->coll, y * 80, x * 80);
                  else if (img->map.grid[x][y] == 'E')
			mlx_put_image_to_window(img->mlx, img->win, img->exit, y * 80, x * 80);
                  else if (img->map.grid[x][y] == 'P')
			mlx_put_image_to_window(img->mlx, img->win, img->down, y * 80, x * 80);
                  y++;
		}
                x++;
	}
}

/*
 * Some garbage
else if (img->map.grid[x][y] == 'UpUPUPUPUPU')
  mlx_put_image_to_window(img.mlx, img.win, img.up, 320, 0);
else if (img->map.grid[x][y] == '1')
      mlx_put_image_to_window(img.mlx, img.win, img.left, 480, 0);
else if (img->map.grid[x][y] == 'P')
      mlx_put_image_to_window(img.mlx, img.win, img.right, 560, 0);
 *
 */

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
	else
		unknown_key_error(img);
	if (can_move == 0)
		return (0);
	img->map.player.moves++;
	ft_putstr_fd("Moves :", 1);
	ft_put_pos_nbr_fd(img->map.player.moves, 1);
	write(1, "\n", 1);
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

int	main(int ac, char **av)
{
	t_data	img;

	//	int		x;
	if (ac < 2 || !ends_by_ber(av[1]))
		input_error();
	img.map.status = 0;
	define_map(&img.map, av[1]);
	if (img.map.status == 0)
		map_error(img.map.grid, img.map.copy);
	img.map.player.moves = 0;
		int x = 0;
		while (img.map.grid[x])
		{
			printf("%s\n", img.map.grid[x]);
			x++;
		}
		x = 0;
		while (img.map.copy[x])
		{
			printf("%s\n", img.map.copy[x]);
			x++;
		}
	img.mlx = mlx_init();
	if (img.mlx == NULL)
		return (1);
	img.win = mlx_new_window(img.mlx, ((img.map.rows + 1) * 80), ((img.map.cols) * 80), "so_long");
	if (img.win == NULL)
	{
		mlx_destroy_display(img.mlx);
		free(img.mlx);
		return (1);
	}
	init_pictures(&img);
	init_images(&img);
	init_map(&img);
	// img.img = mlx_new_image(mlx, 600, 600);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	//		&img.line_length, &img.endian);
	mlx_key_hook(img.win, key_hook, &img);
	mlx_hook(img.win, DestroyNotify, 0, close_window, &img);
	// mlx_put_image_to_window(mlx, mlx_window, img.img, 0,0)
	mlx_loop(img.mlx);
	close_window(&img);
	// mlx_destroy_window(img.mlx, img.win);
	// mlx_destroy_display(img.mlx);
	//   mlx_destroy_image(mlx, &img);
	free(img.mlx);
	return (0);
}

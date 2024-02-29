/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:10:35 by mbernard          #+#    #+#             */
/*   Updated: 2024/02/29 08:30:07 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Convertir image en xpm pour que ca s affiche correctement
 *
 */
#include "so_long.h"

int	close_window(t_data *img)
{
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	ft_free_tab(img->map.grid);
	ft_free_tab(img->map.copy);
	exit(1);
	return (0);
}

int	key_hook(int keysym, t_data *img)
{
	if (keysym == XK_Escape)
	{
		printf("Goodbye!\n");
		close_window(img);
	}
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
	int		x;
	
	if (ac < 2 || !ends_by_ber(av[1]))
		input_error();
	img.map.status = 0;
	define_map(&img.map, av[1]);
	if (img.map.status == 0)
		map_error(img.map.grid, img.map.copy);
	x = 0;
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
	// img.img = mlx_new_image(mlx, 600, 600);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	//		&img.line_length, &img.endian);
	img.win = mlx_new_window(img.mlx, 600, 600, "My First Rainbow");
	if (img.win == NULL)
	{
		mlx_destroy_display(img.mlx);
		free(img.mlx);
		return (1);
	}
	mlx_key_hook(img.win, key_hook, &img);
	mlx_hook(img.win, DestroyNotify, 0, close_window, &img);
	// mlx_put_image_to_window(mlx, mlx_window, img.img, 0,
	//	0);mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(img.mlx);
	close_window(&img);
	// mlx_destroy_window(img.mlx, img.win);
	// mlx_destroy_display(img.mlx);
	//   mlx_destroy_image(mlx, &img);
	free(img.mlx);
	return (0);
}

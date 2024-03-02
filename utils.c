/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:15:47 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/02 13:13:49 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	ft_search_char(char letter, char *charset)
{
	size_t	c;

	c = 0;
	if (charset)
	{
		while (charset[c])
		{
			if (letter == charset[c])
				return (1);
			c++;
		}
	}
	return (0);
}

void	free_tabs(char **map, char **copy)
{
	ft_free_tab(map);
	ft_free_tab(copy);
}

void	ft_put_pos_nbr_fd(size_t n, int fd)
{
	if (n < 10)
		ft_putchar_fd(n + '0', fd);
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}

void	init_pictures(t_data *img)
{
	ft_strlcpy(img->emp_img, "./sprites/empty_80_80.xpm", 26);
	ft_strlcpy(img->wall_img, "./sprites/wall_80_80.xpm", 25);
	ft_strlcpy(img->coll_img, "./sprites/coins_80_80.xpm", 26);
	ft_strlcpy(img->exit_img, "./sprites/chest_80_80.xpm", 26);
	ft_strlcpy(img->up_img, "./sprites/up_80_80.xpm", 23);
	ft_strlcpy(img->down_img, "./sprites/down_80_80.xpm", 25);
	ft_strlcpy(img->left_img, "./sprites/left_80_80.xpm", 25);
	ft_strlcpy(img->right_img, "./sprites/right_80_80.xpm", 26);
}

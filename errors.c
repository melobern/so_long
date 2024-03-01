/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:37:40 by mbernard          #+#    #+#             */
/*   Updated: 2024/02/29 08:53:15 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	no_such_file_error(void)
{	
	write(2, "Error\nNo such file in directory\n", 32);
	exit(EXIT_FAILURE);
}

void	malloc_error(void)
{
	write(2, "Error\nMallor error\n", 19);
	exit(EXIT_FAILURE);
}

void	input_error(void)
{
	write(2, "Error\nNo file.ber given\n", 24);
	exit(EXIT_FAILURE);
}

void	map_error(char **map, char **copy)
{
	ft_free_tab(map);
	ft_free_tab(copy);
	write(2, "Error\nInvalid map\n", 18);
	exit(EXIT_FAILURE);
}

void	unknown_key_error(t_data *img)
{
        write(2, "Error\n", 6);
        write(2, "Unknown key\n", 12);
        close_window(img);
}


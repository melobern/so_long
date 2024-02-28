/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:37:40 by mbernard          #+#    #+#             */
/*   Updated: 2024/02/28 18:17:37 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_perror(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	no_such_file_error(void)
{
	write(2, "Error : No such file in directory\n", 34);
	exit(EXIT_FAILURE);
}

void	malloc_error(void)
{
	write(2, "Error : Mallor error\n", 21);
	exit(EXIT_FAILURE);
}

void	input_error(void)
{
	write(2, "Error : No file.ber given\n", 26);
	exit(EXIT_FAILURE);
}

void	map_error(char **map)
{
	ft_free_tab(map);
	write(2, "Error : invalid map\n", 20);
	exit(EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:37:40 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/03 13:05:45 by mbernard         ###   ########.fr       */
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
	free_tabs(map, copy);
	write(2, "Error\nInvalid map\n", 18);
	exit(EXIT_FAILURE);
}

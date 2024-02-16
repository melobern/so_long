/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:10:35 by mbernard          #+#    #+#             */
/*   Updated: 2024/02/16 13:21:29 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Convertir image en xpm pour que ca s affiche correctement
 *
 */
#include "mlx.h"
#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(void) {
    void *mlx;
    void *mlx_window;
    //t_data	img;

    mlx = mlx_init();
    if (mlx == NULL)
        return (1);
    //img.img = mlx_new_image(mlx, 600, 600);
    //img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    mlx_window = mlx_new_window(mlx, 600, 600, "My First Rainbow");
    if (mlx_window == NULL)
    {
        mlx_destroy_display(mlx);
        free(mlx);
        return (1);
    }
	//mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	//mlx_loop(mlx);

    mlx_destroy_window(mlx, mlx_window);
    mlx_destroy_display(mlx);
 //   mlx_destroy_image(mlx, &img);
    free(mlx);
	return (0);
}

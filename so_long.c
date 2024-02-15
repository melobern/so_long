/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:10:35 by mbernard          #+#    #+#             */
/*   Updated: 2024/02/14 18:58:25 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

typedef struct	s_data {
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}				t_data;

int main(void)
{
    void    *mlx;
    void    *mlx_window;
    t_data  img;

    mlx = mlx_init();
    img.img = mlx_new_image(mlx, 100, 70);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    mlx_window = mlx_new_window(mlx, 500, 500,"my first window");
    mlx_pixel_put(mlx, mlx_window, 250, 255, 0xff0000);
    mlx_loop(mlx);
    return (0);
}

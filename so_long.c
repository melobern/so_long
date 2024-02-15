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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    square(t_data *img, int weight, int height)
{
    int x;
    int y;

    x = 0;
    while (x++ < weight)
    {
        y = 100;
        while (y++ < height) {
            my_mlx_pixel_put(img, x, y, 0x00FF5500);
            my_mlx_pixel_put(img, x + 10, y + 10, 0x00FF0055);
        }
    }
}

int main(void)
{
    void    *mlx;
    void    *mlx_window;
    t_data  img;

    mlx = mlx_init();
    img.img = mlx_new_image(mlx, 200, 200);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    mlx_window = mlx_new_window(mlx, 500, 500,"my first window");
    mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
    square(&img, 300, 200);
    mlx_loop(mlx);
    return (0);
}

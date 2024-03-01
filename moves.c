/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:44:09 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/01 13:44:20 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void  collect_or_leave(t_data *img, char c, size_t x, size_t y)
{
  if (c == 'C')
  {
    img->map.coins--;
    img->map.grid[x][y] = '0';
    printf("%lu coins left !!!\n", img->map.coins);
  }
  else if (c == 'E')
  {
    if (img->map.coins == 0)
    {
      ft_putendl_fd("Congratulations ! You finished the game !", 1);
      ft_putendl_fd("Sprites credits to Cub Noodles ;", 1);
      ft_putendl_fd("https://cupnooble.itch.io/", 1);
      close_window(img);
    }
  }
}

bool move_up(t_data *img)
{
  size_t  x;
  size_t  y;

  x = img->map.player.x;
  y = img->map.player.y;
  if (img->map.grid[x - 1][y] == '1')
    return (0);
  img->map.player.x -= 1;
  collect_or_leave(img, img->map.grid[x - 1][y], x - 1, y);
  return (1);
}

bool move_down(t_data *img)
{

  size_t  x;
  size_t  y;

  x = img->map.player.x;
  y = img->map.player.y;
  if (img->map.grid[x + 1][y] == '1')
    return (0);
  img->map.player.x += 1;
  collect_or_leave(img, img->map.grid[x + 1][y], x + 1, y);
  return (1);
}

bool move_left(t_data *img)
{
  size_t  x;
  size_t  y;

  x = img->map.player.x;
  y = img->map.player.y;
  if (img->map.grid[x][y - 1] == '1')
    return (0);
  img->map.player.y -= 1;
  collect_or_leave(img, img->map.grid[x][y - 1], x - 1, y);
  return (1);
}

bool move_right(t_data *img)
{
  size_t  x;
  size_t  y;

  x = img->map.player.x;
  y = img->map.player.y;
  if (img->map.grid[x][y + 1] == '1')
    return (0);
  img->map.player.y += 1;
  collect_or_leave(img, img->map.grid[x][y + 1], x - 1, y);
  return (1);
}

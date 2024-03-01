/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:44:11 by mbernard          #+#    #+#             */
/*   Updated: 2024/02/28 18:53:08 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h> //TO SUPPREESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS

# define EMPTY '0'
# define WALL '1'
# define PLAYER 'P'
# define COLLECTIBLE 'C'
# define EXIT 'E'

typedef struct s_player
{
	size_t	x;
	size_t	y;
        size_t moves;
}			t_player;

typedef struct s_map
{
  size_t	rows;
  size_t	cols;
  size_t        coins;
  char	**grid;
  char	**copy;
  bool	status;
  t_player player;
}     t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
        void    *empty;
        void    *wall;
        void    *coll;
        void    *exit;
        void    *up;
        void    *down;
        void    *left;
        void    *right;
        char emp_img[26];
        char wall_img[25];
        char coll_img[26];
        char exit_img[26];
        char up_img[23];
        char down_img[25];
        char left_img[25];
        char right_img[26];
	char *addr; // unused for the moment
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_map	map;
}			t_data;

////////////////////////////////////////////////////////////////////////
////////     				 ERRORS                  ///////
////////////////////////////////////////////////////////////////////////
void		unknown_key_error(t_data *img);
void		no_such_file_error(void);
void		malloc_error(void);
void		input_error(void);
void		map_error(char **map, char **copy);
////////////////////////////////////////////////////////////////////////
////////     				 UTILS			////////
////////////////////////////////////////////////////////////////////////
int	close_window(t_data *img);
void		ft_free_tab(char **tab);
bool		ft_search_char(char letter, char *charset);
void	ft_put_pos_nbr_fd(size_t n, int fd);
void	init_pictures(t_data *img);
////////////////////////////////////////////////////////////////////////
////////     				 MAP			////////
////////////////////////////////////////////////////////////////////////
void		define_map(t_map *map, char *ber);
void	        fill_paths(t_map map, size_t x, size_t y);
bool	        check_path(t_map *map);
////////////////////////////////////////////////////////////////////////
////////     				 MOVES			////////
////////////////////////////////////////////////////////////////////////
bool move_up(t_data *img);
bool move_down(t_data *img);
bool move_left(t_data *img);
bool move_right(t_data *img);
#endif

/*
	Votre programme doit prendre en paramètre un fichier de carte se terminant par
			l’extension .ber.
	5
	So Long Et merci pour le poisson !
	IV.1 Le jeu
	• Le but du joueur est de collecter tous les items présents sur la carte,
		puis de
			s’échapper en empruntant le chemin le plus court possible.
	• Les touches W, A,
		S et D doivent être utilisées afin de mouvoir le personnage prin-
	cipal.
	• Le joueur doit être capable de se déplacer dans ces 4 directions : haut,
		bas,
	gauche, droite.
	• Le joueur ne doit pas pouvoir se déplacer dans les murs.
	• À chaque mouvement, le compte total de mouvement doit être affiché dans le
	shell.
	• Vous devez utiliser une vue 2D (vue de haut ou de profil).
	• Le jeu n’a pas à être en temps réel.
	• Bien que les exemples donnés montrent un thème dauphin,
		vous êtes libre de créer
			l’univers que vous voulez
*/

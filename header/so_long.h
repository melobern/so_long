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

# define EMPTY 0
# define WALL 1
# define PLAYER P
# define COLLECTIBLE C
# define EXIT E

typedef struct s_map
{
	size_t	rows;
	size_t	cols;
	char	**grid;
	char	**copy;
	bool	status;
}			t_map;

typedef struct s_player
{
	size_t	x;
	size_t	y;
}			t_player;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char *addr; // unused for the moment
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_map	map;
}			t_data;

////////////////////////////////////////////////////////////////////////
////////     				 ERRORS                  ///////
////////////////////////////////////////////////////////////////////////
void		ft_perror(void);
void		no_such_file_error(void);
void		malloc_error(void);
void		input_error(void);
void		map_error(char **map, char **copy);
////////////////////////////////////////////////////////////////////////
////////     				 UTILS			////////
////////////////////////////////////////////////////////////////////////
void		ft_free_tab(char **tab);
bool		ft_search_char(char letter, char *charset);
////////////////////////////////////////////////////////////////////////
////////     				 MAP			////////
////////////////////////////////////////////////////////////////////////
void		define_map(t_map *map, char *ber);
bool	check_path(t_map map);
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

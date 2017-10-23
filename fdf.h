/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chle-van <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:03:46 by chle-van          #+#    #+#             */
/*   Updated: 2017/10/23 21:22:36 by chle-van         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# define ESC 53
# define ESP 49
# define W 13
# define A 0
# define S 1
# define D 2
# define R 15
# define F 3
# define HAUT 126
# define BAS 125
# define DROITE 124
# define GAUCHE 123
# define PLUS 69
# define MINUS 78
# define CREATE 1
# define APPLY 2
# define ROT 1
# define TRA 2
# define ZC 1
# define LEN 1050
# define WID 1600

typedef struct	s_fdf
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	short			alpha;
	short			beta;
	double			arad;
	double			brad;
	short			zoom;
	int				xmax;
	int				ymax;
	int				**map;
	int				tx;
	int				ty;
	int				tz;
	int				x;
	int				x1;
	int				y;
	int				y1;
	int				dx;
	int				dy;
	int				xm;
	int				ym;
	char			r;
	char			g;
	char			b;

}					t_fdf;

int					ft_fdf(char *filename);
int					ft_draw(t_fdf *fdf);
int					ft_keypress(int key, t_fdf *fdf);

# endif

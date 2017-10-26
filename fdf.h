/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chle-van <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:03:46 by chle-van          #+#    #+#             */
/*   Updated: 2017/10/26 21:20:56 by chle-van         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
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
# define F1 122
# define HAUT 126
# define BAS 125
# define DROITE 124
# define GAUCHE 123
# define PLUS 69
# define MINUS 78

# define YD 1
# define XD 2
# define NOLINE 4
# define CREATE 1
# define APPLY 2
# define RAZ 3
# define ROT 1
# define ROTH 5
# define TRA 20
# define TRAZ 1
# define ZC 1
# define LINERES 100
# define LEN 1050
# define WID 1600

# define ERR_OPEN -1
# define ERR_MAP -2
# define ERR_CMAP -3

typedef struct		s_fdf
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	short			alpha;
	short			beta;
	double			a1;
	double			a2;
	double			b1;
	double			b2;
	double			arad;
	double			brad;
	float			zoom;
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
	double			dx;
	double			dy;
	int				xm;
	int				ym;
	char			r;
	char			g;
	char			b;
	char			pt;
}					t_fdf;

int					ft_fdf(char *filename);
int					ft_draw(t_fdf *fdf);
int					ft_keypress(int key, t_fdf *fdf);
void				ft_create_image(t_fdf *fdf, char flag);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chle-van <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:17:07 by chle-van          #+#    #+#             */
/*   Updated: 2017/10/23 21:22:34 by chle-van         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_initmlx(t_fdf *fdf)
{
	fdf->tx = 0;
	fdf->ty = 0;
	fdf->tz = 0;
	fdf->x = 0;
	fdf->x1 = 0;
	fdf->y = 0;
	fdf->y1 = 0;
	fdf->dx = 0;
	fdf->dy = 0;
	fdf->r = 0xFF;
	fdf->g = 0xFF;
	fdf->b = 0xFF;
	fdf->zoom = 1;
	fdf->xm = WID / 2;
	fdf->ym = LEN / 2;
	fdf->alpha = 30;
	fdf->beta = 30;
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WID, LEN, "FDF");
	mlx_expose_hook(fdf->win, &ft_draw, fdf);
	mlx_key_hook(fdf->win, &ft_keypress, fdf);	
	mlx_loop(fdf->mlx);
	return (0);
}

int				ft_createmap(int fd, t_fdf *fdf)
{
	char **tmp;
	int i;
	int j;
	char *line;

	j = -1;
	i = -1;
	fdf->map = (int **)malloc(sizeof(int *) * fdf->ymax);
	while (++i < fdf->ymax)
	{
		ft_gnl(fd, &line);
		tmp = ft_strsplit(line, ' ');
		fdf->map[i] = (int *)malloc(sizeof(int) * fdf->xmax);
		while (++j < fdf->xmax)
		{
			fdf->map[i][j] = ft_atoi(tmp[j]);
			ft_putnbr(j);
		}
		j = 0;
	}
	return (1);
}

int				ft_check(int fd, t_fdf *fdf)
{
	char *line;

	line = 0;
	if (ft_gnl(fd, &line))
	{
		fdf->xmax = ft_countn(line, ' ');
		ft_strdel(&line);
	}
	else
		return (-1);
	fdf->ymax = 1;
	while (ft_gnl(fd, &line) > 0)
		if (ft_countn(line, ' ') == fdf->xmax)
			fdf->ymax++;
		else
			return (-1);
	ft_putnbr(fdf->xmax);
	ft_putchar(';');
	ft_putnbr(fdf->ymax);
	return (0);
}

int ft_getmap(char *filename, t_fdf *fdf)
{
	int fd;

	if (!(fd = open(filename, O_RDONLY)))
	{
		ft_putstr("err open");
		return (-1);
	}
	if (ft_check(fd, fdf) < 0)
	{
		ft_putstr("err check");
		return (-1);
	}
	close(fd);
	if (!(fd = open(filename, O_RDONLY)))
	{
		ft_putstr("err reopen");
		return (-1);
	}
	//	ft_putstr("map check");
	if(!ft_createmap(fd, fdf))
	{
		ft_putstr("err createmap");
		return (-1);
	}
	return (0);
}


int				ft_fdf(char *filename)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (ft_getmap(filename, fdf) < 0)
	{
		ft_putstr("erreur de lecture.");
		return (-1);
	}
	ft_initmlx(fdf);
	free(fdf);
	return (0);
}

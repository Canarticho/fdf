/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chle-van <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:17:07 by chle-van          #+#    #+#             */
/*   Updated: 2017/10/26 23:46:55 by chle-van         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				ft_initmlx(t_fdf *fdf)
{
	fdf->pt = NOLINE;
	fdf->tx = 0;
	fdf->ty = 0;
	fdf->tz = 0;
	fdf->r = 0xff;
	fdf->g = 0x00;
	fdf->b = 0xff;
	fdf->zoom = 5;
	fdf->xm = WID / 3;
	fdf->ym = LEN / 2;
	fdf->alpha = 0;
	fdf->beta = 300;
	fdf->arad = ft_degtorad(fdf->alpha);
	fdf->brad = ft_degtorad(fdf->beta);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WID, LEN, "FDF");
	ft_create_image(fdf, CREATE);
	mlx_hook(fdf->win, 2, 3, &ft_keypress, fdf);
	mlx_loop_hook(fdf->mlx, &ft_draw, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}

int				ft_createmap(int fd, t_fdf *fdf)
{
	char	**tmp;
	int		i;
	int		j;
	char	*line;

	j = -1;
	i = -1;
	fdf->map = (int **)malloc(sizeof(int *) * fdf->ymax);
	while (++i < fdf->ymax)
	{
		if (ft_gnl(fd, &line) < 0)
			return (-1);
		tmp = ft_strsplit(line, ' ');
		free(line);
		fdf->map[i] = (int *)malloc(sizeof(int) * fdf->xmax);
		while (++j < fdf->xmax)
		{
			fdf->map[i][j] = ft_atoi(tmp[j]);
			free(tmp[j]);
		}
		free(tmp);
		j = -1;
	}
	return (1);
}

int				ft_check(int fd, t_fdf *fdf)
{
	char	*line;
	int		i;
	char	c;

	line = NULL;
	fdf->xmax = 0;
	fdf->ymax = 0;
	while ((c = ft_gnl(fd, &line)) > 0)
	{
		if (!fdf->xmax)
			fdf->xmax = ft_countn(line, ' ');
		if (ft_countn(line, ' ') == fdf->xmax)
		{
			i = -1;
			while (line[++i])
				if (!ft_strchr(" 0123456789-", line[i]))
					return (-1);
			fdf->ymax++;
		}
		else
			return (-1);
		free(line);
	}
	if (c == 0 && fdf->xmax && fdf->ymax)
		return (1);
	return (-1);
}

int				ft_getmap(char *filename, t_fdf *fdf)
{
	int fd;

	if (!(fd = open(filename, O_RDONLY)))
		return (ERR_OPEN);
	if (ft_check(fd, fdf) < 0)
		return (ERR_MAP);
	close(fd);
	if (!(fd = open(filename, O_RDONLY)))
		return (ERR_OPEN);
	if (!ft_createmap(fd, fdf))
		return (ERR_CMAP);
	else
		ft_putstr("Map cree\n");
	return (0);
}

int				ft_fdf(char *filename)
{
	t_fdf	*fdf;
	int		err;

	if (!(fdf = (t_fdf *)malloc(sizeof(t_fdf))))
	{
		ft_putstr("Erreur alloc struct.\n");
		return (-1);
	}
	if ((err = ft_getmap(filename, fdf)) < 0)
	{
		if (err == ERR_MAP)
			ft_putstr("Map invalide.\n");
		else if (err == ERR_OPEN)
			ft_putstr("Fichier invalide.\n");
		else if (err == ERR_CMAP)
			ft_putstr("Erreur creation map.\n");
		return (-1);
	}
	ft_initmlx(fdf);
	free(fdf);
	return (0);
}

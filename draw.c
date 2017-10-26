/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chle-van <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 12:59:40 by chle-van          #+#    #+#             */
/*   Updated: 2017/10/26 23:52:03 by chle-van         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_writepix(t_fdf *fdf, int x, int y, int z)
{
	static int i;
	static int j;

	if (!(i == x && j == y) || (x == 0 && y == 0))
		if (x >= 0 && y >= 0 && x < WID && y < LEN)
		{
			if (z >= 0)
			{
				fdf->data[4 * (x + (y * WID)) + 0] = fdf->b;
				fdf->data[4 * (x + (y * WID)) + 1] = fdf->g;
				fdf->data[4 * (x + (y * WID)) + 2] = fdf->r;
			}
			else
			{
				fdf->data[4 * (x + (y * WID)) + 0] = 0xff;
				fdf->data[4 * (x + (y * WID)) + 1] = 0;
				fdf->data[4 * (x + (y * WID)) + 2] = 0;
			}
		}
	i = x;
	j = y;
}

void		ft_draw_line(t_fdf *fdf, int z)
{
	double	x;
	double	y;
	int		i;

	i = LINERES;
	fdf->dy = fdf->y1 - fdf->y;
	fdf->dx = fdf->x1 - fdf->x;
	x = fdf->x;
	y = fdf->y;
	fdf->dx /= i;
	fdf->dy /= i;
	while (i >= 0)
	{
		ft_writepix(fdf, x, y, z);
		x += fdf->dx;
		y += fdf->dy;
		i--;
	}
}

void		ft_apply(t_fdf *f, int x, int y, char axis)
{
	f->x = f->xm + f->tx + f->zoom * (x * f->a1 + y * f->a2);
	f->y = f->ym + f->ty + f->zoom * (f->b2 * (x * f->a2 - y * f->a1) -
			(f->map[y][x] + f->tz) * f->b1);
	if (!(axis & NOLINE))
	{
		if (axis & YD)
		{
			f->x1 = f->xm + f->tx + f->zoom * (x * f->a1 + (y + 1) * f->a2);
			f->y1 = f->ym + f->ty + f->zoom * (f->b2 * (x * f->a2 -
						(y + 1) * f->a1) - (f->map[y + 1][x] + f->tz) * f->b1);
		}
		else if (axis & XD)
		{
			f->x1 = f->xm + f->tx + f->zoom * ((x + 1) * f->a1 + y * f->a2);
			f->y1 = f->ym + f->ty + f->zoom * (f->b2 * ((x + 1) * f->a2 -
						y * f->a1) - (f->map[y][x + 1] + f->tz) * f->b1);
		}
		ft_draw_line(f, f->map[y][x]);
	}
	else
		ft_writepix(f, f->x, f->y, f->map[y][x]);
}

void		ft_create_image(t_fdf *fdf, char flag)
{
	int bpp;
	int size;
	int endi;

	if (flag == RAZ)
		ft_bzero(fdf->data, 4 * WID * LEN);
	else if (flag == APPLY)
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	else if (flag == CREATE)
	{
		fdf->img = mlx_new_image(fdf->mlx, WID, LEN);
		fdf->data = mlx_get_data_addr(fdf->img, &bpp, &size, &endi);
	}
}

int			ft_draw(t_fdf *fdf)
{
	int x;
	int y;

	y = -1;
	fdf->a1 = cos(fdf->arad);
	fdf->a2 = sin(fdf->arad);
	fdf->b1 = cos(fdf->brad);
	fdf->b2 = sin(fdf->brad);
	ft_create_image(fdf, RAZ);
	while (++y < fdf->ymax)
	{
		x = -1;
		while (++x < fdf->xmax)
		{
			if (x < fdf->xmax - 1)
				ft_apply(fdf, x, y, fdf->pt + XD);
			if (y < fdf->ymax - 1)
				ft_apply(fdf, x, y, fdf->pt + YD);
		}
	}
	ft_create_image(fdf, APPLY);
	return (0);
}

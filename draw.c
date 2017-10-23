/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chle-van <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 12:59:40 by chle-van          #+#    #+#             */
/*   Updated: 2017/10/23 21:08:40 by chle-van         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_writepix(t_fdf *fdf, int x, int y)
{
	if (x > 0 && y > 0 && x < WID && y < LEN)
	{
		fdf->data[x * 4 + y * WID + 1] = fdf->r;
		fdf->data[x * 4 + y * WID + 2] = fdf->g;
		fdf->data[x * 4 + y * WID + 3] = fdf->b;
	}
}

void		ft_draw_line(t_fdf *fdf)
{		
	double hyp;
	double x;
	double y;

	fdf->dy = fdf->y1 - fdf->y;
	fdf->dx = fdf->x1 - fdf->x;
	x = fdf->x;
	y = fdf->y;
	hyp = sqrt((fdf->dx * fdf->dx) + (fdf->dy * fdf->dy));
	fdf->dx /= hyp;
	fdf->dy /= hyp;
	while (hyp >= 0)
	{
		ft_writepix(fdf, x, y);
		x += fdf->dx;
		y += fdf->dy;
		hyp--;
	}
}

void		ft_applyx(t_fdf *fdf, int x, int y)
{
	fdf->x = fdf->xm + fdf->tx + fdf->zoom * (x * cos(fdf->arad) + y * sin(fdf->arad));
	fdf->y = fdf->ym + fdf->ty + fdf->zoom * (sin(fdf->brad) * (x * sin(fdf->arad) - y * cos(fdf->arad)) + 
			fdf->map[y][x] * cos (fdf->brad));
	fdf->x1 = fdf->xm + fdf->tx + fdf->zoom * ((x + 1) * cos(fdf->arad) + y * sin(fdf->arad));
	fdf->y1 = fdf->ym + fdf->ty + fdf->zoom * (sin(fdf->brad) * ((x + 1) * sin(fdf->arad) - 
				y * cos(fdf->arad)) + fdf->map[y][x + 1] * cos(fdf->brad));
	ft_draw_line(fdf);
}

void		ft_applyy(t_fdf *fdf,int x,int y)
{
	fdf->x = fdf->xm + fdf->tx + fdf->zoom * (x * cos(fdf->arad) + y * sin(fdf->arad));
	fdf->y = fdf->ym + fdf->ty + fdf->zoom * (sin(fdf->brad) * (x * sin(fdf->arad) - y * cos(fdf->arad)) + 
			fdf->map[y][x] * cos(fdf->brad));
	fdf->x1 = fdf->xm + fdf->tx + fdf->zoom * ((x) * cos(fdf->arad) + (y + 1) * sin(fdf->arad));
	fdf->y1 = fdf->ym + fdf->ty + fdf->zoom * (sin(fdf->brad) * ((x) * sin(fdf->arad) - 
				(y + 1) * cos(fdf->arad)) + fdf->map[y + 1][x] * cos(fdf->brad));
	ft_draw_line(fdf);
}

void		ft_create_image(t_fdf *fdf, char flag)
{
	int bpp;
	int size;
	int endi;

	if (flag == CREATE)
	{
		fdf->img = mlx_new_image(fdf->mlx, 1600, 1050);
		fdf->data = mlx_get_data_addr(fdf->img, &bpp, &size, &endi);
	}
	else if (flag == APPLY)
	{
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0 ,0);
		mlx_destroy_image(fdf->mlx, fdf->img);
	}
}

int		ft_draw(t_fdf *fdf)
{
	int x;
	int y;

	x = 0;
	y = 0;
	ft_create_image(fdf, CREATE);
	while (y < fdf->ymax)
	{
		while (x < fdf->xmax)
		{
			if (x < fdf->xmax - 1)
				ft_applyx(fdf, x, y);
			if (y < fdf->ymax - 1)
				ft_applyy(fdf, x, y);
					x++;
		}
		x = 0;
		y++;
	}
	ft_create_image(fdf, APPLY);
	return (0);


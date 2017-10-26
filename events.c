/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chle-van <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 13:01:09 by chle-van          #+#    #+#             */
/*   Updated: 2017/10/26 23:07:36 by chle-van         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_zoom(int keycode, t_fdf *fdf)
{
	if (keycode == PLUS || (keycode == MINUS && fdf->zoom > ZC))
		fdf->zoom = (keycode == PLUS) ? (fdf->zoom + ZC) : (fdf->zoom - ZC);
	else if (keycode == F1 && !fdf->pt)
		fdf->pt = NOLINE;
	else if (keycode == F1 && fdf->pt)
		fdf->pt = 0;
}

void	ft_translation(int keycode, t_fdf *fdf)
{
	if (keycode == W || keycode == S)
		fdf->ty = (keycode == S) ? (fdf->ty + TRA) : (fdf->ty - TRA);
	else if (keycode == A || keycode == D)
		fdf->tx = (keycode == D) ? (fdf->tx + TRA) : (fdf->tx - TRA);
	else if (keycode == R || keycode == F)
		fdf->tz = (keycode == R) ? (fdf->tz + TRA) : (fdf->tz - TRA);
}

void	ft_rotate(int keycode, t_fdf *fdf)
{
	if (keycode == GAUCHE)
		fdf->alpha = fdf->alpha % 360 + ROTH;
	else if (keycode == DROITE)
		fdf->alpha = fdf->alpha % 360 - ROTH;
	else if (keycode == BAS)
		fdf->beta = fdf->beta % 360 + ROT;
	else if (keycode == HAUT)
		fdf->beta = fdf->beta % 360 - ROT;
	fdf->arad = ft_degtorad(fdf->alpha);
	fdf->brad = ft_degtorad(fdf->beta);
}

int		ft_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		while (--fdf->ymax)
			free(fdf->map[fdf->ymax]);
		free(fdf->map);
		free(fdf);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == W || keycode == A || keycode == S || keycode == D ||
			keycode == R || keycode == F)
		ft_translation(keycode, fdf);
	else if (keycode == HAUT || keycode == BAS || keycode == DROITE ||
			keycode == GAUCHE)
		ft_rotate(keycode, fdf);
	else if (keycode == PLUS || keycode == MINUS || keycode == F1)
		ft_zoom(keycode, fdf);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chle-van <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 13:01:09 by chle-van          #+#    #+#             */
/*   Updated: 2017/10/23 20:42:25 by chle-van         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_zoom(int keycode, t_fdf *fdf)
{
	if (keycode == PLUS)
		fdf->zoom = fdf->zoom + ZC;
	else
		fdf->zoom = fdf->zoom - ZC;
}

void	ft_translation(int keycode, t_fdf *fdf)
{
	if (keycode == W || keycode == S)
		fdf->tx = (keycode == W) ? (fdf->tx + TRA) : (fdf->tx - TRA);
	else if (keycode == A || keycode == D)
		fdf->ty = (keycode == D) ? (fdf->ty + TRA) : (fdf->ty - TRA);
	else if (keycode == R || keycode == F)
		fdf->tz = (keycode == R) ? (fdf->tz + TRA) : (fdf->tz + TRA);
}

void	ft_rotate(int keycode, t_fdf *fdf)
{
	if (keycode == HAUT)
		fdf->alpha = (fdf->alpha + ROT > 360) ? (fdf->alpha + ROT - 360) : (fdf->alpha + ROT);
	else if (keycode == BAS)
		fdf->alpha = (fdf->alpha - ROT > 360) ? (fdf->alpha - ROT + 360) : (fdf->alpha - ROT);
	else if (keycode == DROITE)
		fdf->beta = (fdf->beta + ROT > 360) ? (fdf->beta + ROT - 360) : (fdf->beta + ROT);
	else if (keycode == GAUCHE)
		fdf->beta = (fdf->beta + ROT > 360) ? (fdf->beta + ROT - 360) : (fdf->beta + ROT);
	fdf->arad = ft_degtorad(fdf->alpha);
	fdf->brad = ft_degtorad(fdf->beta);
}

int		ft_keypress(int keycode, t_fdf *fdf)
{
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
	if (keycode == W || keycode == A || keycode == S || keycode == D || keycode == R || keycode == F)
		ft_translation(keycode, fdf);
	if (keycode == HAUT || keycode == BAS || keycode == DROITE || keycode == GAUCHE)
		ft_rotate(keycode, fdf);
	if (keycode == PLUS || keycode == MINUS)
		ft_zoom(keycode, fdf);
	return (0);
}

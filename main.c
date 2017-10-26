/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chle-van <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:13:01 by chle-van          #+#    #+#             */
/*   Updated: 2017/10/26 23:06:43 by chle-van         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr("Wrong number of arguments.\nUsage: ./fdf \"fdf_map.fdf\"\n");
		return (0);
	}
	return (ft_fdf(av[1]));
}

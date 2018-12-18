/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_hashs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:59:56 by jplevy            #+#    #+#             */
/*   Updated: 2018/12/17 16:32:58 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

uint32_t	leftrotate(uint32_t x, uint32_t c)
{
	return (((x) << (c)) | ((x) >> (32 - (c))));
}

void		md5_hash_0(t_vars *vars, int i)
{
	vars->f = (vars->b & vars->c) | ((~(vars->b)) & vars->d);
	vars->g = i;
}

void		md5_hash_1(t_vars *vars, int i)
{
	vars->f = (vars->d & vars->b) | ((~(vars->d)) & vars->c);
	vars->g = (5 * i + 1) % 16;
}

void		md5_hash_2(t_vars *vars, int i)
{
	vars->f = vars->b ^ vars->c ^ vars->d;
	vars->g = (3 * i + 5) % 16;
}

void		md5_hash_3(t_vars *vars, int i)
{
	vars->f = vars->c ^ (vars->b | ~(vars->d));
	vars->g = (7 * i) % 16;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:10:24 by marvin            #+#    #+#             */
/*   Updated: 2018/11/21 18:10:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

uint64_t		swap_int64(uint64_t in)
{
	uint64_t	out;

	out = (in & 0xff) << 56 | (in & 0xff00) << 40 | (in & 0xff0000) << 24 \
		| (in & 0xff000000) << 8 | (in & 0xff00000000) >> 8 \
		| (in & 0xff0000000000) >> 24 | (in & 0xff000000000000) >> 40 \
		| (in & 0xff00000000000000) >> 56;
	return(out);
}

uint32_t		swap_int32(uint32_t in)
{
	uint32_t	out;

	out = (in & 0xff) << 24 | (in & 0xff00) << 8 | (in & 0xff0000) >> 8 \
		| (in & 0xff000000) >> 24;
	return(out);
}

void			ft_loop_init_vars(t_vars *vars)
{
	vars->a = vars->h0;
	vars->b = vars->h1;
	vars->c = vars->h2;
	vars->d = vars->h3;
	vars->e = vars->h4;
	vars->f = vars->h5;
	vars->g = vars->h6;
	vars->h = vars->h7;
}

void			ft_loop_complete_vars(t_vars *vars)
{
	vars->h0 += vars->a;
	vars->h1 += vars->b;
	vars->h2 += vars->c;
	vars->h3 += vars->d;
	vars->h4 += vars->e;
	vars->h5 += vars->f;
	vars->h6 += vars->g;
	vars->h7 += vars->h;
}

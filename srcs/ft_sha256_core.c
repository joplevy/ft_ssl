/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:08:41 by marvin            #+#    #+#             */
/*   Updated: 2018/11/21 18:08:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

static void	ft_init_loop(t_vars *vars, uint32_t buff[16])
{
	int		i;

	i = -1;
	while (++i < 64)
	{
		if (i < 16)
			vars->w[i] = swap_int32(buff[i]);
		else
			vars->w[i] = ft_min_sig_1(vars->w[i - 2]) + vars->w[i - 7] \
				+ ft_min_sig_0(vars->w[i - 15]) + vars->w[i - 16];
	}
}

static void	ft_process_sha256(t_vars *vars, uint32_t buff[16])
{
	int			i;
	uint32_t	tmp1;
	uint32_t	tmp2;

	ft_init_loop(vars, buff);
	ft_loop_init_vars(vars);
	i = -1;
	while (++i < 64)
	{
		tmp1 = vars->h + ft_maj_sig_1(vars->e) \
			+ ft_ch(vars->e, vars->f, vars->g) + sha256_k[i] + vars->w[i];
		tmp2 = ft_maj_sig_0(vars->a) + ft_maj(vars->a, vars->b, vars->c);
		vars->h = vars->g;
		vars->g = vars->f;
		vars->f = vars->e;
		vars->e = vars->d + tmp1;
		vars->d = vars->c;
		vars->c = vars->b;
		vars->b = vars->a;
		vars->a = tmp1 + tmp2;
	}
	ft_loop_complete_vars(vars);
}

void	ft_sha256(t_args *args)
{
	t_vars	vars;

	vars = ft_init_sha256_vars();
	if (args->fd >= 0)
		ft_fd_hash(args, &vars, &ft_process_sha256);
	else
		ft_str_hash(args, &vars, &ft_process_sha256);
	ft_print_sha256(vars, args);
}

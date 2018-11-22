/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:46:49 by jplevy            #+#    #+#             */
/*   Updated: 2018/11/21 18:20:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

static void	ft_process_md5(t_vars *vars, uint32_t buff[16])
{
	int			i;
	uint32_t	tmp;
	static void	(*md5_hashs[])(t_vars *, int) = \
	{&md5_hash_0, &md5_hash_1, &md5_hash_2, &md5_hash_3};

	ft_loop_init_vars(vars);
	i = -1;
	while (++i < 64)
	{
		md5_hashs[i / 16](vars, i);
		tmp = vars->d;
		vars->d = vars->c;
		vars->c = vars->b;
		vars->b = leftrotate((vars->a + vars->f + md5_k[i] + buff[vars->g]), \
			md5_r[i]) + vars->b;
		vars->a = tmp;
	}
	ft_loop_complete_vars(vars);
}

void		ft_md5(t_args *args)
{
	t_vars	vars;

	vars = ft_init_md5_vars();
	if (args->fd >= 0)
		ft_fd_hash(args, &vars, &ft_process_md5);
	else
		ft_str_hash(args, &vars, &ft_process_md5);
	ft_print_md5(vars, args);
}

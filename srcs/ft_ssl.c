/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 16:14:23 by jplevy            #+#    #+#             */
/*   Updated: 2018/11/21 16:23:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

uint32_t		swap_int32(uint32_t in)
{
	uint32_t	out;

	out = (in & 0xff) << 24 | (in & 0xff00) << 8 | (in & 0xff0000) >> 8 \
		| (in & 0xff000000) >> 24;
	return(out);
}

static void	ft_process_sha256(t_vars *vars, uint32_t buff[16])
{
	int			i;
	uint32_t	tmp1;
	uint32_t	tmp2;

	i = -1;
	while (++i < 64)
	{
		if (i < 16)
			vars->w[i] = swap_int32(buff[i]);
		else
			vars->w[i] = ft_min_sig_1(vars->w[i - 2]) + vars->w[i - 7] \
				+ ft_min_sig_0(vars->w[i - 15]) + vars->w[i - 16];
	}
	vars->a = vars->h0;
	vars->b = vars->h1;
	vars->c = vars->h2;
	vars->d = vars->h3;
	vars->e = vars->h4;
	vars->f = vars->h5;
	vars->g = vars->h6;
	vars->h = vars->h7;
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
	vars->h0 += vars->a;
	vars->h1 += vars->b;
	vars->h2 += vars->c;
	vars->h3 += vars->d;
	vars->h4 += vars->e;
	vars->h5 += vars->f;
	vars->h6 += vars->g;
	vars->h7 += vars->h;
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

int	 	ft_ssl(int ac, char **av)
{
	int		i;
	t_args	args;

	i = -1;
	args = ft_init_args();
	while (++i < NB_HASH)
	{
		if (ft_strcmp(av[0], (funcs_calls[i]).ref) == 0)
		{
			if (ac == 1)
				ft_stdin(&args, (funcs_calls[i]).func_call);
			while (--ac > 0 && ++av)
			{
				args.next = (ac > 0) ? *(av + 1) : NULL;
				if ((*av)[0] == '-')
				{
					ft_get_flags((*av) + 1, &(args), (funcs_calls[i]).func_call);
					if (args.next == args.str && args.last_f == 's' && --ac)
						++av;
				}
				else if ((args.fd = open(*av, O_RDONLY)) > 0)
				{
					args.str = *av;
					(funcs_calls[i]).func_call(&args);
					close(args.fd);
				}
				else
					ft_printf("%s :No such file or directory\n", *av);
			}
			return (1);
		}
	}
	return (0);
}

int	 main(int ac, char **av)
{
	if (ac < 2)
		ft_putstr(USAGE);
	else if (!(ft_ssl(ac - 1, av + 1)))
		ft_printf(FMT, av[1]);
	return (0);
}
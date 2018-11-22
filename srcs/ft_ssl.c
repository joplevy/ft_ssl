/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 16:14:23 by jplevy            #+#    #+#             */
/*   Updated: 2018/11/21 18:57:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void	ft_parse_args(int ac, char **av, t_args *args, int i)
{
	// if (ac == 1)
	// 	ft_stdin(args, (funcs_calls[i]).func_call);
	while (--ac > 0 && ++av)
	{
		args->next = (ac > 0) ? *(av + 1) : NULL;
		if ((*av)[0] == '-')
		{
			ft_get_flags((*av) + 1, args, (funcs_calls[i]).func_call);
			if (args->next == args->str && args->last_f == 's' && --ac)
				++av;
		}
		else if ((args->fd = open(*av, O_RDONLY)) > 0)
		{
			args->str = *av;
			(funcs_calls[i]).func_call(args);
			close(args->fd);
		}
		else
			ft_printf("%s :No such file or directory\n", *av);
	}
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
			ft_parse_args(ac, av, &args, i);
			if (!(args.used))
				ft_stdin(&args, (funcs_calls[i]).func_call);
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
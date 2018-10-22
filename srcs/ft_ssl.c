/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 16:14:23 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/22 20:47:38 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void	ft_md5(t_args *args)
{
	__uint32_t	buff[16];
	int			i;

	if (args->fd >= 0)
	{
		ft_bzero(buff, 16 * sizeof(__uint32_t));
		while (read(args->fd, buff, 16 * sizeof(__uint32_t)) > 0)
		{
			i = -1;
			while (++i < 16)
				ft_printf("%x\n", buff[i]);
			ft_bzero(buff, 16 * sizeof(__uint32_t));
		}
		// ft_printf("should read fd %d\n", args->fd);
	}
	else
		ft_putendl(args->str);
}

void	ft_sha256(t_args *args)
{
	if (args)
		ft_putstr("ft_sha256 call\n");
}

t_args	ft_init_args(void)
{
	t_args	ret;

	ret.fd = -1;
	ret.flag = NONE;
	ret.str = NULL;
	return (ret);
}

void    ft_string(t_args *args, void (*func_call)(t_args *))
{
	args->fd = -1;
	ft_putendl("string call");
	if (args->str)
		func_call(args);
	else
		ft_putendl("option requires an argument -- s");
}
void    ft_stdin(t_args *args, void (*func_call)(t_args *))
{
	ft_putendl("stdin call");
	args->fd = 0;
	func_call(args);
}
void    ft_set_q(t_args *args, void (*func_call)(t_args *))
{
	ft_putendl("set q");
	if (func_call)
		args->flag |= QUIET;
}
void    ft_set_r(t_args *args, void (*func_call)(t_args *))
{
	ft_putendl("set r");
	if (func_call)
		args->flag |= REVERSE;
}

void	ft_get_flags(char *str, t_args *args, void (*func_call)(t_args *))
{
	int		i;
	int		found;

	while (*str)
	{
		args->str = (*(str + 1)) ? str + 1 : args->next;
		i = -1;
		found = 0;
		while (++i < NB_FLAG)
		{
			if (*str == (flag_calls[i]).ref[0])
			{
				args->last_f = *str;
				found = 1;
				(flag_calls[i]).func_call(args, func_call);
				if (*str == 's')
					return;
			}
		}
		if (!found)
			ft_printf("illegal option -- %c\n", *str);
		str++;
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
			if (ac == 1)
			{
				args.fd = 0;
				(funcs_calls[i]).func_call(&args);
			}
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
					(funcs_calls[i]).func_call(&args);
					close(args.fd);
				}
				else
					ft_printf("%s :No such file or directory", *av);
				// av++;
				// ft_putstr(*av);
				// (funcs_calls[i]).func_call(ac - 1, av);
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
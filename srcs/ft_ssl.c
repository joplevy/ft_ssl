/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 16:14:23 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/24 19:09:21 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

uint32_t	ft_floor(double val)
{
	uint32_t	i;

	i = 0;
	while (i < (uint32_t)val)
		i++;
	return (i - 1);
}

t_md5_vars	ft_init_md5_vars(void)
{
	int			i;
	t_md5_vars	vars;
	
	i = -1;
	while (++i < 64)
	{
		vars.md5_k[i] = ft_floor(fabs(sin(i + 1)) * ft_power(2, 32));
		// ft_printf("%u %u\n", vars.md5_k[i], md5_k[i]);
	}
	vars.h0 = 0x67452301;
	vars.h1 = 0xEFCDAB89;
	vars.h2 = 0x98BADCFE;
	vars.h3 = 0x10325476;
	return (vars);
}

uint32_t	leftrotate(uint32_t x, uint32_t c)
{
	return (((x) << (c)) | ((x) >> (32 - (c))));
}

#include <stdio.h>
void	ft_md5(t_args *args)
{
	uint32_t	buff[16];
	uint32_t	tmp;
	int			i;
	int			j;
	size_t		len;
	size_t		total;
	t_md5_vars	vars;
	
	vars = ft_init_md5_vars();
	total = 0;
	if (args->fd >= 0)
	{
		ft_bzero(buff, 16 * sizeof(uint32_t));
		while ((len = read(args->fd, buff, 16 * sizeof(uint32_t))) > 0)
		{
			total += len;
			//faut encore combler avec les zero
			if (len < 14 * sizeof(uint32_t) - 1)
			{
				while (total % 64 != 56)
					total++;
				((char *)buff)[len] = 0x80;
				(buff[14]) = (uint64_t)(total * 8);
				// ft_printf("len id %d just read : %d bytes\n", len, total);
			}
			// if (len < 16 * sizeof(uint32_t))// && len 12 * sizeof(uint32_t))
			// 	buff[len]
			write(1, buff, 16 * sizeof(uint32_t));
			i = -1;
			while (++i < 16)
			{
				vars.a = vars.h0;
				vars.b = vars.h1;
				vars.c = vars.h2;
				vars.d = vars.h3;
				// printf("0x%0.8X\n", buff[i]);
				j = -1;
				while (++j < 64)
				{
					if (j< 16)
					{
						vars.f = (vars.b & vars.c) | ((~(vars.b)) & vars.d);
						vars.g = i;
					}
					else if (j < 32)
					{
						vars.f = (vars.d & vars.b) | ((~(vars.d)) & vars.c);
						vars.g = (5 * j + 1) % 16;
					}
					else if (j < 48)
					{
						vars.f = vars.b ^ vars.c ^ vars.d;
						vars.g = (3 * j + 5) % 16;
					}
					else
					{
						vars.f = vars.c ^ (vars.b | ~(vars.d));
						vars.g = (7 * i) % 16;
					}
					// ft_printf("pre a : %u b : %u c : %u d : %u\n", vars.a, vars.b, vars.c, vars.d);
					tmp = vars.d;
					vars.d = vars.c;
					vars.c = vars.b;
					vars.b = leftrotate((vars.a + vars.f + md5_k[j] + buff[vars.g]), md5_r[j]) + vars.b;
					vars.a = tmp;
					// ft_printf("post a : %u b : %u c : %u d : %u\n", vars.a, vars.b, vars.c, vars.d);
				}
				vars.h0 += vars.a;
				vars.h1 += vars.b;
				vars.h2 += vars.c;
				vars.h2 += vars.d;
			}
			// ft_putchar('\n');
			ft_bzero(buff, 16 * sizeof(uint32_t));
		}
		ft_printf("here it is ==> %0.8x%0.8x%0.8x%0.8x\n", vars.h0, vars.h1, vars.h2, vars.h3);
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
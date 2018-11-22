/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:02:18 by jplevy            #+#    #+#             */
/*   Updated: 2018/11/21 18:55:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

static void	ft_print_hash(uint8_t *hash, size_t len)
{
	size_t		i;
	static char	chars[] = "0123456789abcdef";

	i = 0;
	while (i < len)
	{
		write(1, &(chars[hash[i] / 16]), 1);
		write(1, &(chars[hash[i] % 16]), 1);
		i++;
	}
}

static void	ft_print_all(t_args *args, uint8_t *hash, size_t len)
{
	if (args->flag == NONE)
		ft_printf("MD5 (%c%s%c) = ", args->fd >= 0 ? 0 : '\"', args->str, \
			args->fd >= 0 ? 0 : '\"');
	ft_print_hash(hash, len);
	if ((args->flag & REVERSE) && !(args->flag & QUIET))
	{
		if (args->fd >= 0)
			ft_printf(" *%s", args->str);
		else
			ft_printf(" *\"%s\"", args->str);
	}
	ft_putchar('\n');
	args->used = 1;
}

void		ft_print_md5(t_vars vars, t_args *args)
{
	uint8_t		res[16];
	int			i;
	uint32_t	v[4];

	v[0] = vars.h0;
	v[1] = vars.h1;
	v[2] = vars.h2;
	v[3] = vars.h3;
	i = -1;
	while (++i < 16)
		res[i] = (v[i / 4] >> ((i % 4) * 8)) & 0xFF;
	ft_print_all(args, res, 16);
}

void		ft_print_sha256(t_vars vars, t_args *args)
{
	uint8_t		res[32];

	((uint32_t *)res)[0] = swap_int32(vars.h0);
	((uint32_t *)res)[1] = swap_int32(vars.h1);
	((uint32_t *)res)[2] = swap_int32(vars.h2);
	((uint32_t *)res)[3] = swap_int32(vars.h3);
	((uint32_t *)res)[4] = swap_int32(vars.h4);
	((uint32_t *)res)[5] = swap_int32(vars.h5);
	((uint32_t *)res)[6] = swap_int32(vars.h6);
	((uint32_t *)res)[7] = swap_int32(vars.h7);
	ft_print_all(args, res, 32);
}


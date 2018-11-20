/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:02:18 by jplevy            #+#    #+#             */
/*   Updated: 2018/11/19 16:50:46 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>


static void		ft_print_hash(uint8_t *hash, size_t len)
{
	size_t	i;
	static char	chars[] = "0123456789abcdef";
	
	i = 0;
	while (i < len)
	{
		write(1, &(chars[hash[i] / 16]), 1);
		write(1, &(chars[hash[i] % 16]), 1);
		i++;
	}
}

void		    ft_print_md5(t_md5_vars vars, t_args *args)
{
	uint8_t				res[16];
	int					i;
	uint32_t			*v[4] = {
		&(vars.h0), &(vars.h1), &(vars.h2), &(vars.h3)
	};
	i = -1;
	while (++i < 16)
		res[i] = ((*v)[i / 4] >> ((i % 4) * 8)) & 0xFF;
    if (args->flag == NONE)
        ft_printf("MD5 (%c%s%c) = ", args->fd >= 0 ? 0 : '\"', args->str, \
            args->fd >= 0 ? 0 : '\"');
	ft_print_hash(res, 16);
    if ((args->flag & REVERSE) && !(args->flag & QUIET))
        ft_printf(" %c%s%c", args->fd >= 0 ? 0 : '\"', args->str, \
            args->fd >= 0 ? 0 : '\"');
    ft_putchar('\n');
}
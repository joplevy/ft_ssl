/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:12:46 by jplevy            #+#    #+#             */
/*   Updated: 2018/11/21 18:30:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

t_vars	ft_init_md5_vars(void)
{
	t_vars	vars;

	vars.h0 = 0x67452301;
	vars.h1 = 0xEFCDAB89;
	vars.h2 = 0x98BADCFE;
	vars.h3 = 0x10325476;
	vars.a = 0;
	vars.b = 0;
	vars.c = 0;
	vars.d = 0;
	vars.f = 0;
	vars.g = 0;
	vars.endian = 0;
	return (vars);
}

t_vars	ft_init_sha256_vars(void)
{
	t_vars	vars;

	vars.h0 = 0x6a09e667;
	vars.h1 = 0xbb67ae85;
	vars.h2 = 0x3c6ef372;
	vars.h3 = 0xa54ff53a;
	vars.h4 = 0x510e527f;
	vars.h5 = 0x9b05688c;
	vars.h6 = 0x1f83d9ab;
	vars.h7 = 0x5be0cd19;
	vars.a = 0;
	vars.b = 0;
	vars.c = 0;
	vars.d = 0;
	vars.e = 0;
	vars.f = 0;
	vars.g = 0;
	vars.h = 0;
	vars.endian = 1;
	return (vars);
}

t_args		ft_init_args(void)
{
	t_args	ret;

	ret.fd = -1;
	ret.flag = NONE;
	ret.str = NULL;
	return (ret);
}

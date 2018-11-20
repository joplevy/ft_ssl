/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:12:46 by jplevy            #+#    #+#             */
/*   Updated: 2018/11/19 16:13:39 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>


t_md5_vars	ft_init_md5_vars(void)
{
	t_md5_vars	vars;
	

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
	return (vars);
}

t_args	ft_init_args(void)
{
	t_args	ret;

	ret.fd = -1;
	ret.flag = NONE;
	ret.str = NULL;
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256_sigma_funcs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:28:00 by marvin            #+#    #+#             */
/*   Updated: 2018/11/21 18:28:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

uint32_t	ft_maj_sig_0(uint32_t x)
{
	return (rightrotate(x, 2) ^ rightrotate(x, 13) ^ rightrotate(x, 22));
}

uint32_t	ft_maj_sig_1(uint32_t x)
{
	return (rightrotate(x, 6) ^ rightrotate(x, 11) ^ rightrotate(x, 25));
}

uint32_t	ft_min_sig_0(uint32_t x)
{
	return (rightrotate(x, 7) ^ rightrotate(x, 18) ^ rightshift(x, 3));
}

uint32_t	ft_min_sig_1(uint32_t x)
{
	return (rightrotate(x, 17) ^ rightrotate(x, 19) ^ rightshift(x, 10));
}

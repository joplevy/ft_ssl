/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256_hashs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:05:05 by marvin            #+#    #+#             */
/*   Updated: 2018/12/17 16:51:03 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

uint32_t	rightrotate(uint32_t x, uint32_t c)
{
	return (((x) >> (c)) | ((x) << (32 - (c))));
}

uint32_t	rightshift(uint32_t x, uint32_t c)
{
	return ((x) >> (c));
}

uint32_t	ft_ch(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ ((~x) & z));
}

uint32_t	ft_maj(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

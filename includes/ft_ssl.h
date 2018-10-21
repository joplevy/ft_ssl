/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:39:03 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/21 20:18:14 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# define USAGE "usage: ft_ssl command [command opts] [command args]\n"
# define FMT "ft_ssl: Error: '%s' is an invalid command.\nStandard \
commands:\n\nMessage Digest commands:\nmd5\nsha256\n\nCipher commands:\n"

# include <libft.h>

typedef enum    e_prog{
    MD5,
    SHA256
}               t_prog;

static const void (*hash_funcs[2])(int,char **)  = {
    &ft_md5,
    &ft_sha256,
};

static const char *funcs_call[2]  = {
    "md5",
    "sha256",
};

#endif
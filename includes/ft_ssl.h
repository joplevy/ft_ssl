/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:39:03 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/24 18:01:39 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# define USAGE "usage: ft_ssl command [command opts] [command args]\n"
# define FMT "ft_ssl: Error: '%s' is an invalid command.\nStandard \
commands:\n\nMessage Digest commands:\nmd5\nsha256\n\nCipher commands:\n"
# define NB_FLAG 4
# define NB_HASH 2

# include <libft.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>
# include <math.h>

/*
 -s     string Print a checksum of the given string. | char *

-p      Echo stdin to stdout and append the checksum to stdout. -p | fd

nothing open file | fd

-q      Quiet mode - only the checksum is printed out.  Overrides the -r option.

-r      Reverses the format of the output.  This helps with visual diffs.  Does nothing when combined with the -ptx options.
*/
typedef enum    e_flags{
    NONE, 
    QUIET,
    REVERSE
}               t_flags;

typedef struct  s_args {
    int         fd;
    t_flags     flag;
    char        last_f;
    char        *str;
    char        *next;
}               t_args;

typedef struct  s_funcs {
    char        *ref;
    void        (*func_call)(t_args *);
}               t_funcs;

typedef struct  s_md5_vars {
    uint32_t    h0;
    uint32_t    h1;
    uint32_t    h2;
    uint32_t    h3;
    uint32_t    a;
    uint32_t    b;
    uint32_t    c;
    uint32_t    d;
    uint32_t    f;
    uint32_t    g;
}               t_md5_vars;

typedef struct  s_flag_funcs {
    char        *ref;
    void        (*func_call)(t_args *, void (*)(t_args *));
}               t_flag_funcs;

void    ft_sha256(t_args *args);
void    ft_md5(t_args *args);
void    ft_string(t_args *args, void (*func_call)(t_args *));
void    ft_stdin(t_args *args, void (*func_call)(t_args *));
void    ft_set_q(t_args *args, void (*func_call)(t_args *));
void    ft_set_r(t_args *args, void (*func_call)(t_args *));

static const t_funcs funcs_calls[NB_HASH] = {
    {"md5", &ft_md5},
    {"sha256", &ft_sha256},
};

static const t_flag_funcs flag_calls[NB_FLAG]  = {
    {"s", &ft_string},
    {"p", &ft_stdin},
    {"q", &ft_set_q},
    {"r", &ft_set_r}
};

static const uint32_t   md5_r[64] = {
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

static const uint32_t md5_k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

#endif
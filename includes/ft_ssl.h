/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 15:39:03 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/22 20:21:36 by jplevy           ###   ########.fr       */
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
# include <fcntl.h>
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

#endif
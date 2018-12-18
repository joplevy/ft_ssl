/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 18:28:54 by jplevy            #+#    #+#             */
/*   Updated: 2018/12/17 17:11:44 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# define USAGE "usage: ft_ssl command [command opts] [command args]\n"
# define FMT "ft_ssl: Error: '%s' is an invalid command.\nStandard commands:%s"
# define FMT1 "\n\nMessage Digest commands:\nmd5\nsha256\n\nCipher commands:\n"
# define NB_FLAG 4
# define NB_HASH 2

# include <libft.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>
# include <math.h>

/*
** TYPES
*/

typedef enum	e_flags{
	NONE,
	QUIET,
	REVERSE
}				t_flags;

typedef struct	s_args {
	int			fd;
	t_flags		flag;
	char		last_f;
	char		*str;
	char		*next;
	uint8_t		used;
}				t_args;

typedef struct	s_funcs {
	char		*ref;
	void		(*func_call)(t_args *);
}				t_funcs;

typedef struct	s_vars {
	uint8_t		endian;
	uint32_t	h0;
	uint32_t	h1;
	uint32_t	h2;
	uint32_t	h3;
	uint32_t	h4;
	uint32_t	h5;
	uint32_t	h6;
	uint32_t	h7;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
	uint32_t	w[64];
}				t_vars;

typedef struct	s_flag_funcs {
	char		*ref;
	void		(*func_call)(t_args *, void (*)(t_args *));
}				t_flag_funcs;

/*
** FUNCTIONS
*/

/*
**  ft_printing
*/

void			ft_print_md5(t_vars vars, t_args *args);
void			ft_print_sha256(t_vars vars, t_args *args);

/*
** init
*/

t_vars			ft_init_md5_vars(void);
t_vars			ft_init_sha256_vars(void);
t_args			ft_init_args(void);

/*
**  parsing_launching
*/

void			ft_string(t_args *args, void (*func_call)(t_args *));
void			ft_stdin(t_args *args, void (*func_call)(t_args *));
void			ft_set_q(t_args *args, void (*func_call)(t_args *));
void			ft_set_r(t_args *args, void (*func_call)(t_args *));
void			ft_get_flags(char *str, t_args *args, void (*func_call)\
					(t_args *));

/*
**	ft_ssl_core
*/

void			ft_str_hash(t_args *args, t_vars *vars, \
					void (*func_process)(t_vars *, uint32_t *));
void			ft_fd_hash(t_args *args, t_vars *vars, \
					void (*func_process)(t_vars *, uint32_t *));

/*
**	utils
*/

void			ft_loop_init_vars(t_vars *vars);
void			ft_loop_complete_vars(t_vars *vars);
uint32_t		swap_int32(uint32_t in);
uint64_t		swap_int64(uint64_t in);
int				ft_strcmp_no_case(const char *s1, const char *s2);

/*
**  ft_md5_core
*/

void			ft_md5(t_args *args);

/*
**  ft_md5_hashs
*/

uint32_t		leftrotate(uint32_t x, uint32_t c);
void			md5_hash_0(t_vars *vars, int i);
void			md5_hash_1(t_vars *vars, int i);
void			md5_hash_2(t_vars *vars, int i);
void			md5_hash_3(t_vars *vars, int i);

/*
**	ft_sha256_core
*/

void			ft_sha256(t_args *args);

/*
**	ft_sha256_hashs
*/

uint32_t		rightrotate(uint32_t x, uint32_t c);
uint32_t		rightshift(uint32_t x, uint32_t c);
uint32_t		ft_ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t		ft_maj(uint32_t x, uint32_t y, uint32_t z);

/*
**	ft_sha256_sigma_funcs
*/

uint32_t		ft_maj_sig_0(uint32_t x);
uint32_t		ft_maj_sig_1(uint32_t x);
uint32_t		ft_min_sig_0(uint32_t x);
uint32_t		ft_min_sig_1(uint32_t x);

/*
** STATICS
*/

static const t_funcs g_funcs_calls[NB_HASH] = {
	{"md5", &ft_md5},
	{"sha256", &ft_sha256},
};

static const t_flag_funcs g_flag_calls[NB_FLAG] = {
	{"s", &ft_string},
	{"p", &ft_stdin},
	{"q", &ft_set_q},
	{"r", &ft_set_r}
};
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 18:28:54 by jplevy            #+#    #+#             */
/*   Updated: 2018/11/21 16:25:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# define USAGE "usage: ft_ssl command [command opts] [command args]\n"
# define FMT "ft_ssl: Error: '%s' is an invalid command.\nStandard commands:\
\n\nMessage Digest commands:\nmd5\nsha256\n\nCipher commands:\n"
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
**  ft_md5_hashs
*/

uint32_t		leftrotate(uint32_t x, uint32_t c);
void			md5_hash_0(t_vars *vars, int i);
void			md5_hash_1(t_vars *vars, int i);
void			md5_hash_2(t_vars *vars, int i);
void			md5_hash_3(t_vars *vars, int i);

/*
**  ft_printing
*/

void			ft_print_md5(t_vars vars, t_args *args);
void			ft_print_sha256(t_vars vars, t_args *args);

/*
** init
*/

uint64_t		swap_int64(uint64_t in);
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
**  ft_md5_core
*/

void			ft_str_hash(t_args *args, t_vars *vars, \
					void (*func_process)(t_vars *, uint32_t *));
void			ft_fd_hash(t_args *args, t_vars *vars, \
					void (*func_process)(t_vars *, uint32_t *));
void			ft_md5(t_args *args);
uint32_t		swap_int32(uint32_t in);


/*
**	ft_sha256_hashs
*/
uint32_t		rightrotate(uint32_t x, uint32_t c);
uint32_t		rightshift(uint32_t x, uint32_t c);
uint32_t		ft_ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t		ft_maj(uint32_t x, uint32_t y, uint32_t z);
uint32_t		ft_maj_sig_0(uint32_t x);
uint32_t		ft_maj_sig_1(uint32_t x);
uint32_t		ft_min_sig_0(uint32_t x);
uint32_t		ft_min_sig_1(uint32_t x);

void			ft_sha256(t_args *args);

/*
** STATICS
*/

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
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
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

static const uint32_t sha256_k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,	
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
	
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:46:49 by jplevy            #+#    #+#             */
/*   Updated: 2018/11/21 16:12:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

static void	ft_process_md5(t_vars *vars, uint32_t buff[16])
{
	int			i;
	uint32_t	tmp;
	static void	(*md5_hashs[])(t_vars *, int) = \
	{&md5_hash_0, &md5_hash_1, &md5_hash_2, &md5_hash_3};

	vars->a = vars->h0;
	vars->b = vars->h1;
	vars->c = vars->h2;
	vars->d = vars->h3;
	i = -1;
	while (++i < 64)
	{
		md5_hashs[i / 16](vars, i);
		tmp = vars->d;
		vars->d = vars->c;
		vars->c = vars->b;
		vars->b = leftrotate((vars->a + vars->f + md5_k[i] + buff[vars->g]), \
			md5_r[i]) + vars->b;
		vars->a = tmp;
	}
	vars->h0 += vars->a;
	vars->h1 += vars->b;
	vars->h2 += vars->c;
	vars->h3 += vars->d;
}

void		ft_fd_hash(t_args *args, t_vars *vars, \
	void (*func_process)(t_vars *, uint32_t *))
{
	uint32_t	buff[16];
	size_t		total;
	size_t		len;
	size_t		last_size;

	total = 0;
	ft_bzero(buff, 16 * sizeof(uint32_t));
	while ((len = read(args->fd, buff, 16 * sizeof(uint32_t))) > 0)
	{
		total += len;
		if (len < 16 * sizeof(uint32_t))
			((uint8_t *)buff)[len] = 0x80;
		if (len < 14 * sizeof(uint32_t))
			((uint64_t *)(buff))[7] = vars->endian  ? \
				swap_int64((uint64_t)(total * 8)) : (uint64_t)(total * 8);
		func_process(vars, buff);
		ft_bzero(buff, 16 * sizeof(uint32_t));
	}
	last_size = total % (16 * sizeof(uint32_t));
	if (last_size == 0)
		((uint8_t *)buff)[0] = 0x80;
	if (last_size >= 14 * sizeof(uint32_t) || last_size == 0)
	{
		((uint64_t *)(buff))[7] = vars->endian  ? \
			swap_int64((uint64_t)(total * 8)) : (uint64_t)(total * 8);
		func_process(vars, buff);
	}
}

void		ft_str_hash(t_args *args, t_vars *vars, \
	void (*func_process)(t_vars *, uint32_t *))
{
	char		*tmp;
	uint32_t	buff[16];
	size_t		total;
	size_t		last_size;

	ft_bzero(buff, 16 * sizeof(uint32_t));
	tmp = args->str;
	total = ft_strlen(tmp);
	while (ft_strlen(tmp) >= 16 * sizeof(uint32_t))
	{
		func_process(vars, (uint32_t *)tmp);
		tmp += 16 * sizeof(uint32_t);
	}
	ft_strcpy((char *)buff, tmp);
	last_size = total % (16 * sizeof(uint32_t));
	((uint8_t *)buff)[last_size] = 0x80;
	if (last_size >= 14 * sizeof(uint32_t))
	{
		func_process(vars, buff);
		ft_bzero(buff, 16 * sizeof(uint32_t));
	}
	((uint64_t *)(buff))[7] = vars->endian  ? \
			swap_int64((uint64_t)(total * 8)) : (uint64_t)(total * 8);
	func_process(vars, buff);
}

void		ft_md5(t_args *args)
{
	t_vars	vars;

	vars = ft_init_md5_vars();
	if (args->fd >= 0)
		ft_fd_hash(args, &vars, &ft_process_md5);
	else
		ft_str_hash(args, &vars, &ft_process_md5);
	ft_print_md5(vars, args);
}

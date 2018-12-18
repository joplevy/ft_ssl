/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:09:20 by marvin            #+#    #+#             */
/*   Updated: 2018/12/17 16:54:32 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

static uint64_t	end(uint64_t val, uint8_t endian)
{
	return (endian ? swap_int64(val) : val);
}

void			ft_fd_hash(t_args *args, t_vars *vars, \
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
			((uint64_t *)(buff))[7] = end((uint64_t)(total * 8), vars->endian);
		func_process(vars, buff);
		ft_bzero(buff, 16 * sizeof(uint32_t));
	}
	last_size = total % (16 * sizeof(uint32_t));
	if (last_size == 0)
		((uint8_t *)buff)[0] = 0x80;
	if (last_size >= 14 * sizeof(uint32_t) || last_size == 0)
	{
		((uint64_t *)(buff))[7] = end((uint64_t)(total * 8), vars->endian);
		func_process(vars, buff);
	}
}

void			ft_str_hash(t_args *args, t_vars *vars, \
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
	((uint64_t *)(buff))[7] = end((uint64_t)(total * 8), vars->endian);
	func_process(vars, buff);
}

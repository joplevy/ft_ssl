/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_launching.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:14:26 by jplevy            #+#    #+#             */
/*   Updated: 2018/12/17 14:51:12 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void	ft_string(t_args *args, void (*func_call)(t_args *))
{
	args->fd = -1;
	if (args->str)
		func_call(args);
	else
		ft_putendl("option requires an argument -- s");
}

void	ft_stdin(t_args *args, void (*func_call)(t_args *))
{
	args->fd = 0;
	args->str = "stdin";
	func_call(args);
}

void	ft_set_q(t_args *args, void (*func_call)(t_args *))
{
	if (func_call)
		args->flag |= QUIET;
}

void	ft_set_r(t_args *args, void (*func_call)(t_args *))
{
	if (func_call)
		args->flag |= REVERSE;
}

void	ft_get_flags(char *str, t_args *args, void (*func_call)(t_args *))
{
	int		i;
	int		found;

	while (*str)
	{
		args->str = (*(str + 1)) ? str + 1 : args->next;
		i = -1;
		found = 0;
		while (++i < NB_FLAG)
		{
			if (*str == (g_flag_calls[i]).ref[0])
			{
				args->last_f = *str;
				found = 1;
				(g_flag_calls[i]).func_call(args, func_call);
				if (*str == 's')
					return ;
			}
		}
		if (!found)
			ft_printf("illegal option -- %c\n", *str);
		str++;
	}
}

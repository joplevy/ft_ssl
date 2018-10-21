/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 18:58:53 by jplevy            #+#    #+#             */
/*   Updated: 2018/10/21 20:17:16 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void    ft_md5(int ac, char **av)
{
    if (ac || av)
        ft_putstr("ft_md5 call\n");
}

void    ft_sha256(int ac, char **av)
{
    if (ac || av)
        ft_putstr("ft_md5 call\n");
}

t_prog  ft_get_prog(char *input)
{

}

int     ft_ssl(int ac, char **av)
{
    t_prog  prog;

    prog = ft_get_prog(av[0]);
    hash_funcs[prog](ac, av);
    // if ((ft_strcmp(av[0], "md5")) || (ft_strcmp(av[0], "sha256")))
    //     return (0);
    return (1);
}

int     main(int ac, char **av)
{
    if (ac < 2)
        ft_putstr(USAGE);
    else if (!(ft_ssl(ac - 1, av + 1)))
        ft_printf(FMT, av[1]);
    return (0);
}
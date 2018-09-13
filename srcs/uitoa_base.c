/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uitoa_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 15:48:08 by feedme            #+#    #+#             */
/*   Updated: 2018/09/12 15:04:18 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	ft_spacecount_ub(uintmax_t n, int base)
{
	int	count;

	count = 1;
	while (n >= (uintmax_t)base)
	{
		n /= base;
		count++;
	}
	return (count);
}

char	*ptr_add_x(char *str)
{
	char	*tmp;

	IF_NULL_X((tmp = ft_str_left_ext(str, 2)), -1)
	free(str);
	tmp[0] = '0';
	tmp[1] = 'x';
	return (tmp);
}

char	*uitoa_base(uintmax_t nb, int base, t_params par)
{
	char	*str;
	int		count;
	char	*table;

	table = (par.type == 'X') ? "0123456789ABCDEF" : "0123456789abcdef";
	count = ft_spacecount_ub(nb, base);
	if (nb == 0)
	{
		if (!par.prec)
			return (ft_strnew(0));
		IF_NULL_X((str = ft_strnew(1)), -1)
		str[0] = '0';
		return (str);
	}
	IF_NULL_X((str = ft_strnew(count)), -1)
	while (count > 0)
	{
		str[count - 1] = table[nb % base];
		count--;
		nb /= base;
	}
	if (par.type == 'p')
		str = ptr_add_x(str);
	return (str);
}

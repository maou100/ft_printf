/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 12:16:15 by feedme            #+#    #+#             */
/*   Updated: 2018/09/13 19:42:12 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

char	*apply_char_flags(char c, t_params par)
{
	char	*str;
	int		i;
	int		len;

	len = par.width;
	i = 0;
	IF_NULL_X((str = ft_strnew(len)), -1);
	if (par.min)
	{
		str[i] = c;
		while (++i < len)
			str[i] = ' ';
	}
	else
	{
		len--;
		str[len] = c;
		while (--len >= 0)
			str[len] = par.zero ? '0' : ' ';
	}
	return (str);
}

char	*get_char(va_list ap, t_params par)
{
	char		*str;
	char		c;

	if (par.modif)
		if (par.modif != 'l')
			exit(-1);
	if (!(c = (char)va_arg(ap, int)))
	{
		c = 1;
		g_c_bool = 1;
	}
	if (par.width > 1)
		str = apply_char_flags(c, par);
	else
	{
		IF_NULL_X((str = ft_strnew(1)), -1);
		str[0] = c;
	}
	return (str);
}

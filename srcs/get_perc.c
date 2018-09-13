/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_perc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 13:25:44 by feedme            #+#    #+#             */
/*   Updated: 2018/09/12 10:43:21 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

char	*perc_flags(char *str, t_params par)
{
	char	*tmp;
	int		i;

	i = -1;
	IF_NULL_X((tmp = ft_strnew(par.width)), -1)
	if (par.min)
	{
		tmp[++i] = '%';
		while (++i < par.width)
			tmp[i] = ' ';
	}
	else
	{
		while (++i < par.width - 1)
			tmp[i] = par.zero ? '0' : ' ';
		tmp[i] = '%';
	}
	free(str);
	return (tmp);
}

char	*get_perc(va_list ap, t_params par)
{
	char	*str;

	(void)ap;
	IF_NULL_X((str = ft_strnew(1)), -1)
	str[0] = '%';
	if (par.width > 1)
		str = perc_flags(str, par);
	return (str);
}

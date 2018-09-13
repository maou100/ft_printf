/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:54:06 by feedme            #+#    #+#             */
/*   Updated: 2018/09/12 16:12:15 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_helper_str(int i, char *str, char *tmp, t_params par)
{
		while (str[++i])
			tmp[i] = str[i];
		while (i < par.width)
		{
			tmp[i] = ' ';
			i++;
		}
}

char	*apply_str_flags(char *str, t_params par, int i, int j)
{
	char	*tmp;
	int		len;

	IF_NULL_X((tmp = ft_strnew(par.width)), -1)
	if (par.min)
		ft_helper_str(i, str, tmp, par);
	else
	{
		len = ft_strlen(str);
		while (++i < par.width - len)
			tmp[i] = par.zero ? '0' : ' ';
		while ((i + j) < par.width)
		{
			tmp[i + j] = str[j];
			j++;
		}
	}
//	free(str);
	return (tmp);
}

char	*null_str(void)
{
	char	*str;

	IF_NULL_X((str = ft_strnew(6)), -1)
	str[0] = '(';
	str[1] = 'n';
	str[2] = 'u';
	str[3] = 'l';
	str[4] = 'l';
	str[5] = ')';
	str[6] = '\0';
	return (str);
}

char	*get_str(va_list ap, t_params par)
{
	char	*str;
//	char	*tmp;

	if (par.modif)
		if (par.modif != 'l')
			exit(-1); // on s'occupe pas de S ou ls apparement
	if (!(str = va_arg(ap, char*)))
		str = null_str();
	if (par.prec != -1 && par.prec < ft_strlen(str))
	{
		IF_NULL_X((str = ft_strndup(str, par.prec)), -1)
//		free(str);
//		str = tmp;
//		free(tmp); // not sure
	}
	if (ft_strlen(str) < par.width)
		str = apply_str_flags(str, par, -1, 0);
	return (str);
}

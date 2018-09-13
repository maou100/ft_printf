/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 11:59:44 by feedme            #+#    #+#             */
/*   Updated: 2018/09/05 03:12:01 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

char		*shift_right(char *str, int dist)
{
	int		i;

	i = 0;
	while (str[i] != ' ')
		i++;
	while (--i >= 0)
		str[i + dist] = str[i];
	while (++i < dist)
		str[i] = ' ';
	return (str);
}

char		*octal_hash(char *str, t_params par, int og_len)
{
	char	*tmp;
	int		i;

	i = 0;
	if (par.width > og_len)
	{
		if (par.zero)
			return (str);
		if (par.min)
		{
			str = shift_right(str, 1);
			str[0] = '0';
			return (str);
		}
		else
		{
			while (str[i] == ' ')
				i++;
			str[i - 1] = '0';
			return (str);
		}
	}
	else
	{
		IF_NULL_X((tmp = ft_str_left_ext(str, 1)), -1)
		free(str);
		tmp[0] = '0';
		return (tmp);
	}
}

char		*enuf_space(char *str, t_params par)
{
	int i;

	i = 0;
	if (par.min)
	{
		str = shift_right(str, 2);
//		while (str[i] != ' ')
//			i++;
//		while (--i >= 0)
//			str[i + 2] = str[i];
		str[0] = '0';
		str[1] = par.type == 'X' ? 'X' : 'x';
		return (str);
	}
	else
	{
		if (par.zero)
		{
			str[1] = par.type == 'X' ? 'X' : 'x';
			return (str);
		}
		while (str[i] == ' ')
			i++;
		str[i - 2] = '0';
		str[i - 1] = par.type == 'X' ? 'X' : 'x';
		return (str);
	}
}

char		*apply_hash(char *str, t_params par, int og_len, int prec_len)
{
	char	*tmp;
	int		i;

	i = 0;
	if (par.type == 'o')
		return (octal_hash(str, par, og_len));
	if (par.width - prec_len > 1)
		return (enuf_space(str, par));
	if (par.min)
	{
		if (par.width - prec_len == 1)
		{
			IF_NULL_X((tmp = ft_str_left_ext(str, 1)), -1)
			free(str);
			tmp[0] = par.type == 'X' ? 'X' : 'x';
			tmp = shift_right(tmp, 1);
			tmp[0] = '0';
		}
		else
		{
			IF_NULL_X((tmp = ft_str_left_ext(str, 2)), -1)
			free(str);
			tmp[0] = '0';
			tmp[1] = par.type == 'X' ? 'X' : 'x';
		}
	}
	else
	{
		if (par.width - prec_len == 1)
		{
			IF_NULL_X((tmp = ft_str_left_ext(str, 1)), -1)
		}
		else
			IF_NULL_X((tmp = ft_str_left_ext(str, 2)), -1)
		free(str);
		tmp[0] = '0';
		tmp[1] = par.type == 'X' ? 'X' : 'x';
	}
	return (tmp);	
}

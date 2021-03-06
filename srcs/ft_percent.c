/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 20:35:26 by feedme            #+#    #+#             */
/*   Updated: 2018/09/14 10:14:33 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void		ft_init_fcts(t_fcts *fcts)
{
	fcts['s'] = &get_str;
	fcts['S'] = &get_str;
	fcts['p'] = &get_nbrs;
	fcts['d'] = &get_nbrs;
	fcts['D'] = &get_nbrs;
	fcts['i'] = &get_nbrs;
	fcts['o'] = &get_nbrs;
	fcts['O'] = &get_nbrs;
	fcts['u'] = &get_nbrs;
	fcts['U'] = &get_nbrs;
	fcts['x'] = &get_nbrs;
	fcts['X'] = &get_nbrs;
	fcts['c'] = &get_char;
	fcts['C'] = &get_char;
	fcts['%'] = &get_perc;
}

char		*ft_get_str(va_list ap, t_params par)
{
	char		*tmp;
	t_fcts		tab[121];

	ft_init_fcts(tab);
	if (par.type == 'D' || par.type == 'O' || par.type == 'U')
		par.modif = 'l';
	if (par.type == 'D')
		par.type = 'd';
	if (par.type == 'O')
		par.type = 'o';
	if (par.type == 'U')
		par.type = 'u';
	tmp = (*tab[(int)par.type])(ap, par);
	return (tmp);
}

char		*ft_perc(char *str, int *i, const char *s, va_list ap)
{
	char		*tmp;
	char		*tmp2;
	t_params	par;

	IF_NULL_X((s[++(*i)]), -1);
	ft_init_params(&par);
	while (s[*i])
	{
		if (!IS_TYPE(s[*i]))
			ft_get_params(s, i, &par);
		else
		{
			par.type = s[*i];
			(*i)++;
			break ;
		}
	}
	IF_NULL_R((tmp = ft_get_str(ap, par)), NULL);
	IF_NULL_R((tmp2 = ft_strjoin(str, tmp)), NULL);
	free(str);
	return (tmp2);
}

void		width_hlper(char *str, char *tmp, t_params par, int j)
{
	int			i;

	i = -1;
	if (par.prec != -1)
	{
		while (++i < par.width - ft_strlen(str))
			tmp[i] = ' ';
	}
	else
	{
		while (++i < par.width - ft_strlen(str))
			tmp[i] = par.zero ? '0' : ' ';
	}
	while (str[++j])
		tmp[i + j] = str[j];
}

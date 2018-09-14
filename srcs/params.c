/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 23:01:37 by feedme            #+#    #+#             */
/*   Updated: 2018/09/13 19:24:22 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void		ft_flags(t_params *par, const char *s, int *i)
{
	while (ISFLAG(s[*i]))
	{
		if (s[*i] == '#')
			par->hash = 1;
		else if (s[*i] == '0')
			par->zero = 1;
		else if (s[*i] == '-')
			par->min = 1;
		else if (s[*i] == '+')
			par->plus = 1;
		else if (s[*i] == ' ')
			par->space = 1;
		(*i)++;
	}
	if (!ISDIGIT(s[*i]) && s[*i] != '.' && !ISMODIF(s[*i]) && !IS_TYPE(s[*i]))
		exit(-1);
}

void		ft_width(t_params *par, const char *s, int *i)
{
	int			i0;
	char		*tmp;

	i0 = *i;
	while (ISDIGIT(s[*i]))
		(*i)++;
	IF_NULL_X((tmp = ft_strsub(s, i0, (*i - i0))), -1);
	par->width = ft_atoi(tmp);
	free(tmp);
	if (s[*i] != '.' && !ISMODIF(s[*i]) && !IS_TYPE(s[*i]))
		exit(-1);
}

void		ft_prec(t_params *par, const char *s, int *i)
{
	int			i0;
	char		*tmp;

	(*i)++;
	if (!ISDIGIT(s[*i]))
	{
		if (!ISMODIF(s[*i]) && !IS_TYPE(s[*i]))
			exit(-1);
		par->prec = 0;
		return ;
	}
	i0 = *i;
	while (ISDIGIT(s[*i]))
		(*i)++;
	IF_NULL_X((tmp = ft_strsub(s, i0, (*i - i0))), -1);
	par->prec = ft_atoi(tmp);
	free(tmp);
	if (!ISMODIF(s[*i]) && !IS_TYPE(s[*i]))
		exit(-1);
}

void		ft_modif(t_params *par, const char *s, int *i)
{
	if (s[*i] == 'h')
		par->modif = s[(*i) + 1] == 'h' ? 'H' : 'h';
	else if (s[*i] == 'l')
		par->modif = s[(*i) + 1] == 'l' ? 'L' : 'l';
	else if (s[*i] == 'j')
		par->modif = 'j';
	else if (s[*i] == 'z')
		par->modif = 'z';
	(*i)++;
	if (s[*i] == 'h' || s[*i] == 'l')
		(*i)++;
	if (!IS_TYPE(s[*i]))
		exit(-1);
}

void		ft_get_params(const char *s, int *i, t_params *par)
{
	if (!IS_ANYFLAG(s[*i]))
		exit(-1);
	if (ISFLAG(s[*i]))
		ft_flags(par, s, i);
	if (ISDIGIT(s[*i]))
		ft_width(par, s, i);
	if (s[*i] == '.')
		ft_prec(par, s, i);
	if (ISMODIF(s[*i]))
		ft_modif(par, s, i);
	if (par->space && par->plus)
		par->space = 0;
}

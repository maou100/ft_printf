/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nbrs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:52:47 by feedme            #+#    #+#             */
/*   Updated: 2018/09/13 20:13:34 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

char		*int_prec(char *str, t_params par, char booly)
{
	char		*tmp;
	int			i;
	int			j;
	int			len;

	IF_NULL_X((tmp = ft_strnew(booly ? par.prec + 1 : par.prec)), -1);
	i = -1;
	j = -1;
	len = booly ? ft_strlen(str) - 1 : ft_strlen(str);
	while (++i < par.prec - len)
		tmp[i] = '0';
	while (str[++j])
		tmp[i + j] = str[j];
	free(str);
	return (tmp);
}

char		*int_width(char *str, t_params par)
{
	char		*tmp;
	int			i;

	i = -1;
	IF_NULL_X((tmp = ft_strnew(par.width)), -1);
	if (par.min)
	{
		while (str[++i])
			tmp[i] = str[i];
		i--;
		while (++i < par.width)
			tmp[i] = ' ';
	}
	else
		width_hlper(str, tmp, par, -1);
	free(str);
	return (tmp);
}

char		*ft_left_ext(char *str, int extension)
{
	char	*tmp;
	int		i;
	int		len;

	len = ft_strlen(str) + extension;
	i = 0;
	IF_NULL_R((tmp = ft_strnew(len)), NULL);
	ft_bzero(tmp, len);
	while (extension + i < len)
	{
		tmp[extension + i] = str[i];
		i++;
	}
	return (tmp);
}

char		*int_add_sign(char *str, t_params par)
{
	char		*tmp;

	if (par.width <= par.prec)
	{
		IF_NULL_X((tmp = ft_left_ext(str, 1)), -1);
		free(str);
		tmp[0] = par.space ? ' ' : '+';
		return (tmp);
	}
	else
	{
		if (par.min)
		{
			str = shift_right(str, 1);
			str[0] = par.space ? ' ' : '+';
		}
		else
			str[0] = par.space ? ' ' : '+';
		return (str);
	}
}

char		*get_nbrs(va_list ap, t_params par)
{
	char		*str;
	uintmax_t	nb;
	int			base;
	int			og_len;
	int			prec_len;

	if (par.prec != -1 || par.min || par.type == 'p')
		par.zero = 0;
	if (par.type == 'd' || par.type == 'i' || par.type == 'D')
		return (get_ints(ap, par));
	nb = modif_uints(ap, par);
	base = get_base(par.type);
	str = uitoa_base(nb, base, par);
	og_len = ft_strlen(str);
	if (par.prec > og_len)
		str = int_prec(str, par, 0);
	prec_len = ft_strlen(str);
	if (par.width > prec_len)
		str = int_width(str, par);
	if (par.hash && (((par.type == 'x' || par.type == 'X') && nb) ||
	(par.type == 'o' && par.prec <= og_len)))
		str = apply_hash(str, par, og_len, prec_len);
	return (str);
}

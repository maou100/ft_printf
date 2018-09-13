/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nbrs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:52:47 by feedme            #+#    #+#             */
/*   Updated: 2018/09/13 14:07:56 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

// bcp de problemes a regler, dont le pb des signes devant la precision ou width et flag zero

intmax_t	modif_ints(va_list ap, t_params par)
{
	intmax_t	nb;

	if (par.modif == 'l')
		nb = va_arg(ap, long);
	else if (par.modif == 'L')
		nb = va_arg(ap, long long);
	else if (par.modif == 'j')
		nb = va_arg(ap, intmax_t);
	else if (par.modif == 'z')
		nb = va_arg(ap, ssize_t);
	else
		nb = va_arg(ap, int);
	if (par.modif == 'h')
		nb = (short)nb;
	else if (par.modif == 'H')
		nb = (char)nb;
	return (nb);
}

char		*int_prec(char *str, t_params par, char booly) // s'occuper du probleme de negatif
{
	char		*tmp;
	int			i;
	int			j;
	int			len;

	IF_NULL_X((tmp = ft_strnew(booly ? par.prec + 1 : par.prec)), -1)
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
	int			j;

	i = -1;
	j = -1;
	IF_NULL_X((tmp = ft_strnew(par.width)), -1)
	if (par.min)
	{
		while (str[++i])
			tmp[i] = str[i];
		i--;
		while (++i < par.width)
			tmp[i] = ' ';
	}
	else
	{
		if (par.prec != -1)
		{
			while (++i < par.width - ft_strlen(str))
				tmp[i] = ' ';
		}
		else
		{
			while (++i < par.width - ft_strlen(str)) // s'occuper du probleme du negatif avec width et flag 0
				tmp[i] = par.zero ? '0' : ' ';
		}
		while (str[++j])
			tmp[i + j] = str[j];
	}
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
	IF_NULL_R((tmp = ft_strnew(len)), NULL)
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
		IF_NULL_X((tmp = ft_left_ext(str, 1)), -1)
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

char		*ft_fix_pbs(char *str, t_params par, int booly)
{
	int			i;
	int			j;

	j = 0;
	i = 0;
	if (booly && (par.zero || par.prec != -1))
	{
		while (str[i] != '-')
			i++;
		if (i != 0)
		{
			str[i] = '0';
			while (str[j] != '0')
				j++;
			str[j] = '-';
		}
	}
	else if (par.plus && !par.zero)
	{
		if (str[0] == '+' && str[1] == ' ')
		{
			i++;
			while (str[i] == ' ')
				i++;
			str[i - 1] = '+';
			str[0] = ' ';
		}
	}
	return (str);
}

char		*get_ints(va_list ap, t_params par)
{
	intmax_t	nb;
	char		*str;
	int			len;
	int			booly;

	booly = 0;
	if ((nb = modif_ints(ap, par)) < 0)
		booly = 1;
	if (!nb && !par.prec)
		str = ft_strnew(0);
	else
		IF_NULL_X((str = ft_imaxtoa(nb)), -1)
	len = ft_strlen(str);
	if (par.prec > (booly ? len - 1 : len))
		str = int_prec(str, par, booly);
	if (par.width > ft_strlen(str))
		str = int_width(str, par);
	if ((par.space && nb > 0) || (par.plus && nb >= 0)) 
		str = int_add_sign(str, par);
	str = ft_fix_pbs(str, par, booly); 
	return (str);
}

uintmax_t	modif_uints(va_list ap, t_params par)
{
	uintmax_t	nb;

	if (par.modif == 'l')
		nb = va_arg(ap, unsigned long);
	else if (par.modif == 'L' || par.type == 'O' || par.type == 'U')
		nb = va_arg(ap, unsigned long long);
	else if (par.modif == 'j')
		nb = va_arg(ap, uintmax_t);
	else if (par.modif == 'z')
		nb = va_arg(ap, size_t);
	else
		nb = va_arg(ap, unsigned long long);
	if (par.modif == 'h')
		nb = (unsigned short)nb;
	else if (par.modif == 'H')
		nb = (unsigned char)nb;
	if ((par.type == 'x' || par.type == 'X') && nb > 4294967295 && !par.modif)
		return (0);
	return (nb);
}

//char		*ft_repair(char *str, t_params par, int neg)
//{
//	if (
//}

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
	if (par.hash && (((par.type == 'x' || par.type == 'X') && nb) || (par.type == 'o' && par.prec <= og_len)))
		str = apply_hash(str, par, og_len, prec_len);
//	str = ft_repair(str, par, nb < 0 ? 1 : 0);
	return (str);
}
